/*global define:false*/
define(function() {
	return {
		/**
		 * Transform text into a URL slug: spaces turned into dashes, remove non alnum
		 * @param {String} text
		 */
		slugify: function slugify(text) {
			text = text.replace(/[^-a-zA-Z0-9,&\s]+/ig, '');
			text = text.replace(/-/gi, "_");
			text = text.replace(/\s/gi, "-");
			return text.toLowerCase();
		},
		
		/**
		 * Generate an array of problem letters, e.g. ["A", "B", "C", ..., "J"]
		 * @param {Integer} total
		 */
		generateProblemList: function generateProblemList(total) {
			var problems = [];
			for (var i = 0; i < total; ++i) {
				problems.push(String.fromCharCode("A".charCodeAt(0) + i));
			}
			return problems;
		},
		
		/**
		 * Convert second to minute
		 */
		secondToMinute: function secondToMinute(second) {
			return Math.round(second / 60);
		}
	};
});
