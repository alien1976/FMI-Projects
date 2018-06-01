"use strict";
var typeFunctionalsBorderRadius = "<label>Top Left</label> &nbsp;<input class='form-control topLeft' type='number' value='0'></input>&nbsp;</br>"
    + "<label>Top Right</label> &nbsp;<input class='form-control topRight' type='number' value='0'></input>&nbsp;</br>"
    + "<label>Bottom Left</label> &nbsp;<input class='form-control bottomLeft' type='number' value='0'></input>&nbsp; </br>"
    + "<label>Bottom Right</label> &nbsp;<input class='form-control bottomRight' type='number' value='0'></input>&nbsp;";
function radiusBorder(headText, nameSelector, selector) {
    var arrItems = [];
    arrItems.push("Generate" + headText + "CSS");
    arrItems.push(nameSelector);
    arrItems.push(selector);
    arrItems.push(typeFunctionalsBorderRadius);
    createRadius(arrItems);
}
function radiusTextarea() {
    var arr = [];
    arr.push("-webkit-border-radius:" + $(".topLeft").val() + "px " + $(".topRight").val() + "px " + $(".bottomLeft").val() + "px " + $(".bottomRight").val() + "px;");
    arr.push("border-radius:" + $('.topLeft').val() + 'px ' + $('.topRight').val() + 'px ' + $('.bottomLeft').val() + 'px ' + $('.bottomRight').val() + 'px;');
    return arr;
}
var radiusPreview = function () {
    var preview = $("#preview").css({
        "border-radius": $(".topLeft").val() + "px "
        + $(".topRight").val() + "px " + $(".bottomLeft").val() + "px "
        + $(".bottomRight").val() + "px"
    });
    return preview;
}
var PreviewAreaRadius = function () {
    $('#preview').remove();
    var preview = $(".form-group").append("<div id='preview'></div>")
        + $("#preview").css('display', 'block') +
        radiusPreview();
    return preview;
}

function createRadius(arrItems) {
    $('.modal-backdrop').css('display', 'block');
    $('.form-inline').css('display', 'block');
    $(".form-group").empty();
    $('.modal-head-h3').empty();
    $('.modal-head-h3').append(arrItems.shift());
    $(".form-group").append(arrItems);
    $("body").toggleClass("dialogIsOpen");
    $(".form-group").change(onSmthRadius).keyup(onSmthRadius);
}

function onSmthRadius() {
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
    var TextareaChange = radiusTextarea();
    for (var i = 0; i < TextareaChange.length; i++) {
        $('#txtarea').append(TextareaChange[i]);
        $('#txtarea').append(newline);
    }
    if ($(".nameSelector").val() || selector === "all elements") $('#txtarea').append("}");
    PreviewAreaRadius();
}
