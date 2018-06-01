"use strict";
var typeFunctionalsBoxShadow =
    "<label>Horizontal Length</label> &nbsp;<input class='form-control Horizontal' type='number' value='0'></input>&nbsp;</br>"
    + "<label>Vertical Length</label> &nbsp;<input class='form-control VerticalLength' type='number' value='0'></input>&nbsp;</br>"
    + "<label>Blur Radius</label> &nbsp;<input class='form-control BlurRadius' type='number' value='0'></input>&nbsp;</br>"
    + "<label>Spread</label> &nbsp;<input class='form-control Spred' type='number' value='0'></input>&nbsp;</br>"
    + "<label>Color</label> &nbsp;<input class='form-control jscolor' value='ab2567'></br>"
    + "<label>Inset</label> &nbsp;<select class='form-control Inset' name='Inset'>"
    + "<option value=''>No</option>"
    + "<option value='inset'>Yes</option>"
    + "</select></br>";
function ShadowBox(headText, nameSelector, selector) {
    var arrItems = [];
    arrItems.push("Generate" + headText + "CSS");
    arrItems.push(nameSelector);
    arrItems.push(selector);
    arrItems.push(typeFunctionalsBoxShadow);
    createBoxShadow(arrItems);
}
function ShadowBoxTextarea() {
    var arr = [];
    if ($(".jscolor").val()) {
        arr.push("-webkit-box-shadow:" + $(".Inset").val() + " " + $(".Horizontal").val() + "px " + $(".VerticalLength").val()
            + "px " + $(".BlurRadius").val() + "px " + $(".Spred").val() + "px " + "#" + $(".jscolor").val() + ";");
        arr.push("box-shadow:" + $(".Inset").val() + " " + $(".Horizontal").val() + "px " + $(".VerticalLength").val()
            + "px " + $(".BlurRadius").val() + "px " + $(".Spred").val() + "px " + "#" + $(".jscolor").val() + ";");
    } else {
        arr.push("-webkit-box-shadow:" + $(".Inset").val() + " " + $(".Horizontal").val() + "px " + $(".VerticalLength").val()
            + "px " + $(".BlurRadius").val() + "px " + $(".Spred").val() + "px " + ";");
        arr.push("box-shadow:" + $(".Inset").val() + " " + $(".Horizontal").val() + "px " + $(".VerticalLength").val()
            + "px " + $(".BlurRadius").val() + "px " + $(".Spred").val() + "px " + ";");
    }

    return arr;
}
var ShadowBoxPreview = function () {
    var preview;
    if ($(".jscolor").val()) {
        preview = $("#preview").css({
            "box-shadow": $(".Inset").val() + " " + $(".Horizontal").val() + "px "
            + $(".VerticalLength").val() + "px " + $(".BlurRadius").val() + "px "
            + $(".Spred").val() + "px " + "#" + $(".jscolor").val()
        });
    } else {
        preview = $("#preview").css({
            "box-shadow": $(".Inset").val() + " " + $(".Horizontal").val() + "px "
            + $(".VerticalLength").val() + "px " + $(".BlurRadius").val() + "px "
            + $(".Spred").val() + "px"
        });
    }
    return preview;
}
var PreviewAreaBoxShadow = function () {
    $('#preview').remove();
    var preview = $(".form-group").append("<div id='preview'></div>")
        + $("#preview").css('display', 'block') +
        ShadowBoxPreview();
    return preview;
}
function createBoxShadow(arrItems) {
    $('.modal-backdrop').css('display', 'block');
    $('.form-inline').css('display', 'block');
    $(".form-group").empty();
    $('.modal-head-h3').empty();
    $('.modal-head-h3').append(arrItems.shift());
    $(".form-group").append(arrItems);
    jscolor.installByClassName("jscolor");
    $("body").toggleClass("dialogIsOpen");
    $(".form-group").change(onSmthBoxShadow).keyup(onSmthBoxShadow);
}
function onSmthBoxShadow() {
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
    var TextareaChange = ShadowBoxTextarea();
    for (var i = 0; i < TextareaChange.length; i++) {
        $('#txtarea').append(TextareaChange[i]);
        $('#txtarea').append(newline);
    }
    if ($(".nameSelector").val() || selector === "all elements") $('#txtarea').append("}");
    PreviewAreaBoxShadow();
}
