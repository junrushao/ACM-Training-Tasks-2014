/*global define:false*/

/**
 * Controller for problem quick search
 * Relies on "judge.problems.views.QuickSearchApiView"
 */

define(["jquery"], function ($) {
	function ProblemQuickSearchController(options) {
		this.container = options.container;
		this.apiUrl = options.apiUrl;
	}

	ProblemQuickSearchController.prototype.initialize = function initialize() {
		var $container = $(this.container);
		var $listView = $container.find("ul");
		var $searchBox = $container.find("input");
		var apiUrl = this.apiUrl;
		$container.on("change", "input", function() {
			$listView.html("<li>Searching...</li>").listview("refresh");
			$.get(apiUrl, { keywords: $searchBox.val() }, function(data) {
				$listView.empty();
				$.each(data, function(index, value) {
					var text = [
						"<h1>", value.id, ".", value.title, "</h1>",
						"<p><strong>Source:</strong>", value.source, "</p>",
						"<p><strong>OJ:</strong>", value.residing_judge, ". ", value.residing_judge_id, "</p>"
					].join("");
					$listView.append($("<li data-icon='false'><a href='#'>" + text + "</a></li>").data("problemInfo", value));
				});
				if (data.length === 0) {
					$listView.html("<li>No Search Result</li>");
				}
				$listView.listview("refresh");
			}).fail(function() {
				$listView.html("<li>ERROR DURING SEARCH. CONTACT STAFF.</li>").listview("refresh");
			});
		});
	};

	ProblemQuickSearchController.prototype.attachHandler = function attachHandler(event, callback) {
		$(this.container).on(event, "ul li", function(index, node) {
			callback($(node).data("problemInfo"));
		});
	};

	return ProblemQuickSearchController;
});