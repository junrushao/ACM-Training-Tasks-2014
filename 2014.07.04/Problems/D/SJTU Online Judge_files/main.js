/*global require:false*/
/*global Modernizr:false*/

(function() {
	
if (!Modernizr.cssgradients) {
	require(["jquery"], function($) {
		$(function() {
			$("body").css("opacity", "1");
			$("body").html("<h1>SJTU Online Judge</h1><p>Your Web Browser is too old and is not supported. Please upgrade to latest Chrome/Firefox/Safari, thank you</p><p>请升级您的浏览器。我们推荐最新的Chrome、Firefox或者Safari</p>");
		});
	});
	return;
}

require.config({
	urlArgs : "bust=" + (new Date().getTime())
});

require(["jquery", "judge/bootstrap", "jquery.mobile"], function($, bootstrap) {
	bootstrap();
});

})();
