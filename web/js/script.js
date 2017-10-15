jQuery(function($){
    $("#login_dialog").hide();
    $("#signup_dialog").hide();
    var cookie = Cookies.get('cookie');

    function send_login() {
        var query = {};
        query['user'] = $("#login_dialog form input[name='user']").val();
        query['password'] = $("#login_dialog form input[name='password']").val();

        $.ajax({
            url : '/login',
            type : 'POST',
            dataType : 'JSON',
            data : JSON.stringify(query),
            success : function(data, statut) {
                if (data["status"] == "ok") {
                    cookie = data["cookie"];
                    $("#login_dialog").dialog('close');
                    Cookies.set('cookie', cookie);
                }
                console.log(data);
            }
        });
        return false;
    }

    function send_signup() {
        var query = {};
        query['user'] = $("#signup_dialog form input[name='user']").val();
        query['password'] = $("#signup_dialog form input[name='password']").val();
        query['cookie'] = cookie;

        console.log(JSON.stringify(query));
        $.ajax({
            url : '/signup',
            type : 'POST',
            dataType : 'JSON',
            data : JSON.stringify(query),
            success : function(data, statut) {
                if (data["status"] == "ok") {
                    $("#signup_dialog").dialog('close');
                }
                console.log(data);
            }
        });
        return false;
    }

    function get_client_list() {
        var query = {};
        query['cookie'] = cookie;

        console.log(JSON.stringify(query));
        $.ajax({
            url : '/client_list',
            type : 'POST',
            dataType : 'JSON',
            data : JSON.stringify(query),
            success : function(data, statut) {
                var display = "";
                for (var i = 0 ; i < data['list'].length; i += 1) {
                    var value;
                    if (data['list'][i]['name'])
                        value = data['list'][i]['name'];
                    else
                        value = data['list'][i]['cookie'];
                    display += "<p>" + value + "</p>";
                }
                $('#clientlist_display').html(display);
            }
        });
        return false;
    }

    $('#bar #login').click(function() {
        if (!cookie) {
            $("#login_dialog").dialog();
            $("#login_dialog form").submit(send_login);
        }
        return false;
    });

    $('#bar #signup').click(function() {
        $("#signup_dialog").dialog();
        $("#signup_dialog form").submit(send_signup);
        return false;
    });

    $('#bar #clientlist').click(function() {
        if (cookie) {
            get_client_list();
        } else {
            $("#login_dialog").dialog();
        }
        return false;
    });

    $('body').on('click','.ui-widget-overlay', function() {
        $('.ui-dialog').filter(function () {
            return $(this).css("display") === "block";
        }).find('.ui-dialog-content').dialog('close');
    });
});
