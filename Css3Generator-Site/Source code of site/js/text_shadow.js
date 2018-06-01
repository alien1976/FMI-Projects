"use strict";
var typeFunctionalsTextShadow =
    "<label>Horizontal Length</label> &nbsp;<input class='form-control Horizontal' type='number' value='0'></input>&nbsp; px</br>"
    + "<label>Vertical Length</label> &nbsp;<input class='form-control VerticalLength' type='number' value='0'></input>&nbsp; px</br>"
    + "<label>Blur Radius</label> &nbsp;<input class='form-control BlurRadius' type='number' value='0'></input>&nbsp; px</br>"
    + "<label>Shadow Color</label> &nbsp;<input class='form-control jscolor' value='ab2567'></input></br>"
function TextShadow(headText, nameSelector, selector) {
    var arrItems = [];
    arrItems.push("Generate" + headText + "CSS");
    arrItems.push(nameSelector);
    arrItems.push(selector);
    arrItems.push(typeFunctionalsTextShadow);
    createTextShadow(arrItems);
}
function TextShadowTextarea() {
    var arr = [];
    if ($(".jscolor").val()) {
        arr.push("text-shadow: " + $(".Horizontal").val() + "px " + $(".VerticalLength").val()
            + "px " + $(".BlurRadius").val() + "px " + "#" + $(".jscolor").val() + ";");
    } else {
        arr.push("text-shadow: " + $(".Horizontal").val() + "px " + $(".VerticalLength").val()
            + "px " + $(".BlurRadius").val() + "px " + ";");
    }
    return arr;
}
var TextShadowPreview = function () {
    var preview;
    if ($(".jscolor").val()) {
        preview = $("#preview").css({
            "text-shadow": $(".Horizontal").val() + "px "
            + $(".VerticalLength").val() + "px " + $(".BlurRadius").val() + "px " + "#" + $(".jscolor").val()
        });
    } else {
        preview = $("#preview").css({
            "text-shadow": $(".Horizontal").val() + "px "
            + $(".VerticalLength").val() + "px " + $(".BlurRadius").val() + "px"
        });
    }
    return preview;
}
var PreviewAreaTextShadow = function () {
    $('#preview').remove();
    var preview = $(".form-group").append("<div id='preview'>Cool Text</div>")
        + $("#preview").css('display', 'block') +
        TextShadowPreview();
    return preview;
}
function createTextShadow(arrItems) {
    $('.modal-backdrop').css('display', 'block');
    $('.form-inline').css('display', 'block');
    $(".form-group").empty();
    $('.modal-head-h3').empty();
    $('.modal-head-h3').append(arrItems.shift());
    $(".form-group").append(arrItems);
    jscolor.installByClassName("jscolor");
    $("body").toggleClass("dialogIsOpen");
    $(".form-group").change(onSmthTextShadow).keyup(onSmthTextShadow);
}
function onSmthTextShadow() {
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
    var TextareaChange = TextShadowTextarea();
    for (var i = 0; i < TextareaChange.length; i++) {
        $('#txtarea').append(TextareaChange[i]);
        $('#txtarea').append(newline);
    }
    if ($(".nameSelector").val() || selector === "all elements") $('#txtarea').append("}");
    PreviewAreaTextShadow();
}
