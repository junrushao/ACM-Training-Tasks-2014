/*global define:false*/
/**
 * This module defines a data model class which represents a contest standings.
 */

define(["jquery", "judge/utils"], function($, utils) {
	/**
	 * Represents a standings
	 */
	function Standings(info) {
		this.problemCount = info && info.problemCount || 0;
		this.users = info && info.users || [];
		this.usersType = info && info.usersType || {};
		this.allUsersType = info && info.allUsersType || {};
		this.submissions = info && info.submissions || [];
		this.frozenSince = info && info.frozenSince || 1e9;
	}
	
	/**
	 * Add users in this standings board.
	 * Shadow users' IDs should be "s{{ shadowID }}_{{ userID }}"
	 * @param {Array} users -- an array like [[user_id, user_name], ...],
	 */
	Standings.prototype.addUsers = function(users) {
		for (var i = 0; i < users.length; ++i) {
			this.users.push(users[i]);
		}
	};
	
	/**
	 * Add submissions to this standings board.
	 * @param {Array} submissions -- an array like [{
	 *		user: Unique user id,
	 *		problem: Problem id like "A"
	 *		ac: true/false
	 *		pending: true/false
	 *		time: the submission's time (in second)
	 *	}, ...],
	 */
	Standings.prototype.addSubmissions = function(submissions) {
		for (var i = 0; i < submissions.length; ++i) {
			this.submissions.push(submissions[i]);
		}
		this.submissions.sort(function(a,b) {
			return a["time"] - b["time"];
		});
	};
	
	/**
	 * Generate the standings
	 *
	 * Available options:
	 * - now: generate a standings at a specific minute
	 *
	 * Will set the following attributes:
	 * - this.rank
	 *   An array like [[userId, userName], ...]
	 * - this.userStatus
	 *   An hashmap from userId to {tried: .., pending: .., accepted: ..}
	 * - this.problemStatus
	 *   An hashmap from problem letter (A,B,C,...) to {accepted: .., attempts: ..}
	 */
	Standings.prototype.generate = function(options) {
		var userStatus = {}, problemStat = {};
		var problems = utils.generateProblemList(this.problemCount);
		var now = options && options.now !== undefined ? options.now : 1e9;
		var frozenSince = this.frozenSince || 1e9;

		// Initialize the data structure
		$.each(this.users, function() {
			var userId = this[0];
			userStatus[userId] = {
				accepted: 0,
				tried: 0,
				penalty: 0,
				rating: 0,
				problemStatus: {}
			};
			$.each(problems, function() {
				userStatus[userId].problemStatus[this] = {
					tried: 0,
					pending: 0,
					accepted: 0
				};
			});
		});
		$.each(problems, function() {
			problemStat[this] = {accepted: 0, attempts: 0};
		});
		$.each(this.submissions, function() {
			var s = this;
			var user = s.user;
			var problem = s.problem;
			var time = s.time;
			if (time > now) {
				return;
			}
			if (time > frozenSince) {
				s = $.extend({}, s);
				s.ac = false;
				s.pending = true;
			}
			// Ignore this submission if already accepted
			if (userStatus[user].problemStatus[problem].accepted) {
				return;
			}
			var ustatus = userStatus[user];
			var pstatus = userStatus[user].problemStatus[problem];
			problemStat[problem].attempts += 1;
			ustatus.tried += 1;
			pstatus.tried += 1;
			pstatus.accepted += s.ac ? 1 : 0;
			if (s.pending) {
				pstatus.pending += 1;
			} else if (s.ac) {
				problemStat[problem].accepted += 1;
				pstatus.accepted += 1;
				pstatus.accepted_time = time;
				ustatus.accepted += 1;
				ustatus.penalty += time + 20 * 60 * (pstatus.tried - 1);
			}
		});
		// compute the rank
		var rank = this.users.slice();
		rank.sort(function(a, b) {
			var ua = userStatus[a[0]], ub = userStatus[b[0]];
			if (ua.accepted !== ub.accepted) {
				return -(ua.accepted - ub.accepted);
			} else {
				return ua.penalty - ub.penalty;
			}
		});
		this.rank = rank;
		this.userStatus = userStatus;
		this.problemStat = problemStat;
		return true;
	};
	return Standings;
});
