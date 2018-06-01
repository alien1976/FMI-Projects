"use strict";
var typeFunctionalsBoxResizing =
    "<label>Box Resize:</label> &nbsp;<select name='resizing' class='form-control resizing'>"
    + "<option value='none'>None</option>"
    + "<option value='both'>Both</option>"
    + "<option value='horizontal'>Horizontal</option>"
    + "<option value='vertical'>Vertical</option>"
    + "<option value='initial'>Initial</option>"
    + "<option value='inherit'>Inherit</option></select></br>";

function BoxResizing(headText, nameSelector, selector) {
    var arrItems = [];
    arrItems.push("Generate" + headText + "CSS");
    arrItems.push(nameSelector);
    arrItems.push(selector);
    arrItems.push(typeFunctionalsBoxResizing);
    createBoxResizing(arrItems);
}

function BoxResizingTextarea() {
    var arr = [];
    arr.push("resize:" + $(".resizing").val() + ";");
    return arr;
}

var BoxResizingPreview = function () {
    var preview;
    preview = $("#preview").css({ "resize": $(".resizing").val(), "overflow": "auto" });
    return preview;
}

var PreviewAreaBoxResizing = function () {
    $('#preview').remove();
    var preview = $(".form-group").append("<div id='preview'>Pull the bottom right corner!</div>")
        + $("#preview").css('display', 'block') +
        BoxResizingPreview();
    return preview;
}

function createBoxResizing(arrItems) {
    $('.modal-backdrop').css('display', 'block');
    $('.form-inline').css('display', 'block');
    $(".form-group").empty();
    $('.modal-head-h3').empty();
    $('.modal-head-h3').append(arrItems.shift());
    $(".form-group").append(arrItems);
    $("body").toggleClass("dialogIsOpen");
    $(".form-group").change(onSmthBoxResizing).keyup(onSmthBoxResizing);
}
function onSmthBoxResizing() {
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
    var TextareaChange = BoxResizingTextarea();
    for (var i = 0; i < TextareaChange.length; i++) {
        $('#txtarea').append(TextareaChange[i]);
        $('#txtarea').append(newline);
    }
    if ($(".nameSelector").val() || selector === "all elements") $('#txtarea').append("}");
    PreviewAreaBoxResizing();
}