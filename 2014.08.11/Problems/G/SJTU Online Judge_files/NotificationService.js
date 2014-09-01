/*global define:false*/
/*global alert:false*/
define(["jquery"], function($) {
    var singleton = function() {
        function checkMessages() {
            $.get("/notification/check/", function(data) {
                if (data && data.length !== 0) {
                    for (var i = 0; i < data.length; ++i) {
                        alert(data[i]);
                    }
                }
            });
            setTimeout(checkMessages, 10000);
        }
        return {
            start: function() {
                checkMessages();
            }
        };
    };
    return singleton();
});