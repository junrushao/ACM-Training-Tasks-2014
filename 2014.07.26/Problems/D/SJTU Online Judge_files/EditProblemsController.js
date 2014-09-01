/*global define:false*/
/*global alert:false*/
/**
 * Controller for edit problems
 */
define(["jquery"], function ($) {
	function EditProblemsController(options) {
		this.root = $(options.container);
		this.csrftoken = $(this.root).data("csrftoken");
		this.container = $(options.container).find(".list-container");
		this.apiUrl = options.apiUrl;
		this.button = $(options.container).find("a.js-submit");
	}

	EditProblemsController.prototype.refresh = function() {
		$(this.container).find("ul").listview("refresh");
		$(this.container).find("ul li").each(function(index, value) {
			var char = String.fromCharCode("A".charCodeAt(0) + index);
			$(value).find(".char").html(char);
		});
	};

	EditProblemsController.prototype.addProblem = function(problemId, problemTitle) {
		var $listItem = $("<li></li>").data("icon", false).data("problemId", problemId);
		var char = String.fromCharCode("A".charCodeAt(0) + this.$listView.find("li").length);
		var $listLink = $("<a></a>").attr("href", "#").html(
			"<h1>[<span class='char'>" + char + "</span>] " + problemId + ". " + problemTitle +
			"</h1><p><a href='#' class='js-up'>Up</a> | <a href='#' class='js-down'>Down</a> | <a href='#' class='js-delete'>Delete</a></p>"
		);

		$listItem.append($listLink);
		this.$listView.append($listItem);
		this.refresh();
	};

	EditProblemsController.prototype.initialize = function initialize() {
		var $container = $(this.container);
		var $listView = $("<ul></ul>").data("inset", true);
		$container.empty();
		$container.append($listView);
		$listView.listview();
		this.$listView = $listView;
		$.get(this.apiUrl, { action: "get_problem_list" }, $.proxy(function(data) {
			$.each(data, $.proxy(function(index, value) {
				this.addProblem(value[0], value[1]);
			}, this));
		}, this)).fail(function() {
			alert("Failed to initialize Edit Problem Widget.");
		});
		var self = this;
		$(this.container).on("click", ".js-up", function() {
			var $item = $(this).closest("li");
			if ($item.prev().length) {
				$item.insertBefore($item.prev());
				self.refresh();
			}
		});
		$(this.container).on("click", ".js-down", function() {
			var $item = $(this).closest("li");
			if ($item.next().length) {
				$item.insertAfter($item.next());
				self.refresh();
			}
		});
		$(this.container).on("click", ".js-delete", function() {
			var $item = $(this).closest("li");
			$item.remove();
			self.refresh();
		});
		$(this.root).on("click", ".js-submit", $.proxy(function() {
			this.update();
		}, this));
	};

	EditProblemsController.prototype.getList = function getList() {
		var list = [];
		$(this.container).find("li").each(function(index, node) {
			var id = $(node).data("problemId");
			list.push(id);
		});
		return list;
	};


	EditProblemsController.prototype.update = function update() {
		var list = this.getList();
		$.post(this.apiUrl, {
			action: "update_problem_list",
			problem_list: JSON.stringify(list),
			csrfmiddlewaretoken: this.csrftoken
		}, function() {
			alert("Successfully Updated!");
		}).fail(function() {
			alert("Failed to update!");
		});
	};

	return EditProblemsController;
});