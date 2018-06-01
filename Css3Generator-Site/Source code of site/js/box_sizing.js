"use strict";
"use strict";
var typeFunctionalsBoxSizing =
    "<label>BoxSizing: </label>&nbsp; <select name='sizing' class='form-control sizing'>"
    + "<option value='border'>Border Box</option>"
    + "<option value='content'>Content Box</option></select></br>"
    + "<label>Width</label> &nbsp;<input class='form-control width' type='number'></input>&nbsp; px</br>"
    + "<label>Height</label> &nbsp;<input class='form-control height' type='number'></input>&nbsp; px</br>";

function BoxSizing(headText, nameSelector, selector) {
    var arrItems = [];
    arrItems.push("Generate" + headText + "CSS");
    arrItems.push(nameSelector);
    arrItems.push(selector);
    arrItems.push(typeFunctionalsBoxSizing);
    createBoxSizing(arrItems);
}

function BoxSizingTextrea() {
    var arr = [];
    if ($(".width").val())
        arr.push("width:" + $(".width").val() + "px;");
    if ($(".height").val())
        arr.push("height:" + $(".height").val() + "px;");
    arr.push("box-sizing:" + $(".sizing").val() + ";");
    return arr;
}

var BoxSizingPreview = function () {
    var preview;
    if ($(".width").val() && $(".height").val()) {
        preview = $("#preview").css({ "width": $(".width").val() + "px", "height": $(".height").val() + "px", "box-sizing": $(".sizing").val() });
    }
    else if (!$(".width").val() && $(".height").val()) {
        preview = $("#preview").css({ "height": $(".height").val() + "px", "box-sizing": $(".sizing").val() });
    }
    else if ($(".width").val() && !$(".height").val()) {
        preview = $("#preview").css({ "width": $(".width").val() + "px", "box-sizing": $(".sizing").val() });
    }
    else {
        preview = $("#preview").css({ "box-sizing": $(".sizing").val() });
    }
    return preview;
}
var PreviewAreaBoxSizing = function () {
    $('#preview').remove();
    var preview = $(".form-group").append("<div id='preview'></div>")
        + $("#preview").css('display', 'block') +
        BoxSizingPreview();
    return preview;
}

function createBoxSizing(arrItems) {
    $('.modal-backdrop').css('display', 'block');
    $('.form-inline').css('display', 'block');
    $(".form-group").empty();
    $('.modal-head-h3').empty();
    $('.modal-head-h3').append(arrItems.shift());
    $(".form-group").append(arrItems);
    $("body").toggleClass("dialogIsOpen");
    $(".form-group").change(onSmthBoxSizing).keyup(onSmthBoxSizing);
}

function onSmthBoxSizing() {
    $('#txtarea').empty();
    var newline = String.fromCharCode(13, 10);
    var selector = $(".selector").val();
    if ($(".nameSelector").val()) {
        switch (selector) {
            case "id": $('#txtarea').append("#" + $(".nameSelector").val()); break;
            case "class": $('#txtarea').append("." + $(".nameSelector").val()); break;
            case "element": $('#txtarea').append($(".nameSelector").val()); break;
            case "all elements": $('#txtarea').append("*"); break;
        }
        $('#txtarea').append(" {");
        $('#txtarea').append(newline);
    } else if (selector === "all elements") {
        $('#txtarea').append("* {");
        $('#txtarea').append(newline);
    }
    var TextareaChange = BoxSizingTextrea();
    for (var i = 0; i < TextareaChange.length; i++) {
        $('#txtarea').append(TextareaChange[i]);
        $('#txtarea').append(newline);
    }
    if ($(".nameSelector").val() || selector === "all elements") $('#txtarea').append("}");
    PreviewAreaBoxSizing();
}
