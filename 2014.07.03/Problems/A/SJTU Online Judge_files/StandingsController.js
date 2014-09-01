/*global define:false*/
/*global alert:false*/
/**
 * Controller for standings
 */
define(["jquery", "judge/models/Standings", "judge/renderers/StandingsRenderer", "judge/utils"], function($, Standings, StandingsRenderer, utils) {
	/**
	 * Create a new standings controller
	 * Options:
	 * - container: the DOM node of the container
	 */
	function StandingsController(options) {
		this.dom = $(options.container);
		var $dom = this.dom;
		var $tableContainer = $dom.find(".standings-table-container");
		var $panel = $("#standings-submissions-panel");
		var deferreds = [$.Deferred()];
		var standings = new Standings();
		var renderer = new StandingsRenderer({model: standings});
		
		// Set up displayed user types
		var userType = $dom.data("user-type");
		if (userType === null) {
			$dom.find(".standings-user-type-filter input[type='checkbox']").each(function() {
				$(this).attr("checked", true).checkboxradio("refresh");
			});
		} else {
			$dom.find("#id_type-" + userType.toLowerCase()).attr("checked", true).checkboxradio("refresh");
		}
		
		this.model = standings;
		this.renderer = renderer;
		
		// Retrieve standings data for this contest
		$.get($dom.data("data-url"), {}, function(data) {
			standings.addUsers(data.users);
			standings.addSubmissions(data.submissions);
			standings.problemCount = data.problemCount;
			standings.usersType = {};
			$.each(data.usersType, function() {
				standings.usersType[this[0]] = this[1];
				standings.allUsersType[this[1]] = true;
			});
			deferreds[0].resolve();
		}).fail(function() {
			deferreds[0].reject();
		});
		// Retrieve data for shadow contests
		var shadows = $dom.data("shadow-list");
        shadows.push($dom.data("pk"));
		var shadowUrl = $dom.data("shadow-url");
		$.each(shadows, function(index, shadow_id) {
			var thisDeferred = $.Deferred();
			deferreds.push(thisDeferred);
			$.get(shadowUrl, { pk: shadow_id, external_only: shadow_id === $dom.data("pk") }, function(data) {
				standings.addUsers(data.users);
				standings.addSubmissions(data.submissions);
				thisDeferred.resolve();
			}).fail(function() {
				thisDeferred.reject();
			});
		});
		// When all data are ready, generate the standings
		$.when.apply($, deferreds).done(function() {
			standings.generate({now: $dom.data("now") * 60});
			renderer.options.hiddenTypes = [];
			/*
			$dom.find("input[name='displayed-user-type']").each(function() {
				if (!this.checked) {
					renderer.options.hiddenTypes.push($(this).val());
				}
			});
			*/
			$tableContainer.html(renderer.renderHtml());
			$dom.find(".standings-user-type-filter fieldset").html(renderer.renderUserTypeFilter()).trigger("create").controlgroup();
		});

		$dom.closest(".ui-page").on("click", "#standings-submissions-panel button.compare", function() {
			var checkboxes = $panel.find("input[type=checkbox]:checked");
			if (checkboxes.length !== 2) {
				alert("Select 2 submissions to compare");
				return false;
			}
			var id1 = $(checkboxes[0]).closest("tr").data("id");
			var id2 = $(checkboxes[1]).closest("tr").data("id");
			// $.mobile.changePage($(this).data("compare-url") + "?code1=" + id1 + "&code2=" + id2, {"role": "dialog"});
			window.open($(this).data("compare-url") + "?code1=" + id1 + "&code2=" + id2, '_blank');
		}).on("click", ".standings-container.superuser-mode td.js-clickable", function() {
			var user = $(this).closest("tr").data("user");
			var problem = $(this).data("problem");
			$panel.panel("open").find(".container").html("Loading...");
			$panel.trigger("updatelayout");
			$.get($dom.data("submissions-url"), {
				user : user,
				problem : problem
			}, function(data) {
				var html = ["<table class='full center-aligned table-stroke'><thead><tr><th></th><th>Verdict</th><th>Time</th></tr></thead><tbody>"];
				for (var i = 0; i < data.length; ++i) {
					html.push("<tr data-id='" + data[i].pk + "'><td><input type='checkbox'></td><td>");
					html.push("<a class='verdict verdict-" + utils.slugify(data[i].verdict) + "' href='/submissions/" + data[i].pk + "'>");
					html.push(data[i].verdict);
					html.push("</a></td><td>");
					html.push(data[i].time);
					html.push("</td></tr>");
				}
				html.push("</tbody></table>");
				html = html.join("");
				$panel.find(".container").html(html);
				$panel.trigger("create");
				$panel.trigger("updatelayout");
			});
		}).on("slidestop", "input[name='standings-time']", function() {
			if (standings) {
				standings.generate({
					now : $(this).val() * 60
				});
				$tableContainer.html(renderer.renderHtml());
			}
		}).on("change", "input[name='displayed-user-type']", function() {
			renderer.options.hiddenTypes = [];
			$dom.find("input[name='displayed-user-type']").each(function() {
				if (!this.checked) {
					renderer.options.hiddenTypes.push($(this).val());
				}
			});
			$tableContainer.html(renderer.renderHtml());
		});
	}
	return StandingsController;
});
