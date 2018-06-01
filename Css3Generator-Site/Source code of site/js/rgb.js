"use strict";
var typeFunctionalsRGB =
    "<label>R</label> &nbsp;<input class='form-control R' type='number' value='0'></input>&nbsp; px</br>"
    + "<label>G</label> &nbsp;<input class='form-control G' type='number' value='0'></input>&nbsp; px</br>"
    + "<label>B</label> &nbsp;<input class='form-control B' type='number' value='0' ></input>&nbsp; px</br>"
    + "<label>Opacity</label> &nbsp;<input class='form-control Opacity' type='number' value='1' max='1' min='0' step='0.1'></input></br>"
function RGB(headText, nameSelector, selector) {
    var arrItems = [];
    arrItems.push("Generate" + headText + "CSS");
    arrItems.push(nameSelector);
    arrItems.push(selector);
    arrItems.push(typeFunctionalsRGB);
    createRGB(arrItems);
}
function RGBTextarea() {
    var arr = [];
    arr.push("background-color: rgba(" + $(".R").val() + ", " + $(".G").val()
        + ", " + $(".B").val() + ", " + $(".Opacity").val() + ");");
    arr.push("color: rgba(" + $(".R").val() + ", " + $(".G").val()
        + ", " + $(".B").val() + ", " + $(".Opacity").val() + ");");
    return arr;
}
var RGBPreview = function () {
    var preview;
    preview = $("#preview").css({
        "background-color": "rgba(" + $(".R").val() + "," + $(".G").val()
        + "," + $(".B").val() + "," + $(".Opacity").val() + ")"
    });
    return preview;
}
var PreviewAreaRGB = function () {
    $('#preview').remove();
    var preview = $(".form-group").append("<div id='preview'></div>")
        + $("#preview").css('display', 'block') +
        RGBPreview();
    return preview;
}
function createRGB(arrItems) {
    $('.modal-backdrop').css('display', 'block');
    $('.form-inline').css('display', 'block');
    $(".form-group").empty();
    $('.modal-head-h3').empty();
    $('.modal-head-h3').append(arrItems.shift());
    $(".form-group").append(arrItems);
    $("body").toggleClass("dialogIsOpen");
    $(".form-group").change(onSmthRGB).keyup(onSmthRGB);
}
function onSmthRGB() {
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
    var TextareaChange = RGBTextarea();
    for (var i = 0; i < TextareaChange.length; i++) {
        $('#txtarea').append(TextareaChange[i]);
        $('#txtarea').append(newline);
    }
    if ($(".nameSelector").val() || selector === "all elements") $('#txtarea').append("}");
    PreviewAreaRGB();
}
