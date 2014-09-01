/*global define:false*/
/**
 * This module defines a Renderer class, which generates HTML markups for a standings
 */
define(["jquery", "judge/utils"], function($, utils) {
	/**
	 * Construct a new renderer
	 * Available options:
	 * - model: the data model (judge/models/Standings) to render
	 *
	 * @param {Object} options
	 */
	var defaultOptions = {
		/* An array of user types (A/B/C/D) that should be hidden */
		hiddenTypes: []
	};
	function StandingsRenderer(options) {
		this.model = options.model || options;
		this.options = $.extend({}, defaultOptions, options);
	}
	
	/**
	 * Renders the standings to HTML
	 * All available options is documented in defaultOptions
	 * @param {Object} options
	 */
	StandingsRenderer.prototype.renderHtml = function renderHtml() {
		var options = this.options;
		var html = [];
		var model = this.model;
		var hiddenTypes = {};
		var problems = utils.generateProblemList(model.problemCount);
		$.each(options.hiddenTypes, function() {
			hiddenTypes[this] = true;
		});
		html.push("<table class='standings'><thead><tr><th class='rank-cell'></th> <th class='user-cell'>User</th>");
		for (var i = 0; i < problems.length; ++i) {
			html.push("<th><a href='../problem-" + problems[i] + "/'>" + problems[i] + "</a></th>");
		}
		html.push("<th>Total</th><th>Penalty</th></tr></thead><tbody>");
		$.each(model.rank, function(i) {
			var user = this[0] + "";
			if (hiddenTypes[model.usersType[this[0]]]) {
				return;
			}
			if (user[0] !== "s") {
				html.push("<tr data-user='" + user + "'><td class='rank-cell'>" + (i + 1) + "</td><td class='user-cell " + utils.slugify(model.usersType[this[0]]) + "'>" + this[1] + "</td>");
			} else {
				var realId = user.split("_")[1];
				var shadowId = user.split("_")[0].substr(1);
				html.push("<tr  class='shadow' data-user='" + realId + "'><td>" + (i + 1) + "</td><td>" + this[1] + " (" + shadowId + ")</td>");
			}
			var ustatus = model.userStatus[user];
			$.each(problems, function() {
				var status = model.userStatus[user].problemStatus[this];
				html.push("<td data-problem='" + this + "' ");
				if (status.accepted) {
					html.push("class='pcell js-clickable accepted-cell'><div class='r1'>" + status.tried + "Y</div><div class='r2'>" + utils.secondToMinute(status.accepted_time) + "</div></td>");
				} else if (status.pending) {
					html.push("class='pcell js-clickable pending-cell'>" + (status.tried - status.pending) + "+" + (status.pending) + "</td>");
				} else if (status.tried) {
					html.push("class='pcell js-clickable tried-cell'>" + (status.tried) + "</td>");
				} else {
					html.push("class='pcell'></td>");
				}
			});
			html.push("<td>" + ustatus.accepted + "/" + ustatus.tried + "</td><td>" + utils.secondToMinute(ustatus.penalty) + "</td></tr>");
		});
		return html.join("");
	};

	/**
	 * Renders the user type filter, returns the HTML structure.
	 */
	StandingsRenderer.prototype.renderUserTypeFilter = function renderUserTypeFilter() {
		var model = this.model;
		var html = [];
		for (var userType in model.allUsersType) {
			var id = "id_type-" + utils.slugify(userType);
			html.push("<input checked='checked' type='checkbox' name='displayed-user-type' id='" + id + "' value='" + userType + "'>" +
					"<label for='" + id + "'>" + userType + "</label></input>");
		}
		return html.join("");
	};
	
	return StandingsRenderer;
});
