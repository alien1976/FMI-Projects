"use strict";
var typeFunctionalsFlex =
    "<label>Flex Display:</label> &nbsp;<select name='flex' class='form-control form-control flex'>"
    + "<option value='flex'>Flex</option>"
    + "<option value='inline-flex'>Inline Flex</option></select></br>"
    + "<label>Flex Direction:</label> &nbsp;<select name='flexdir' class='form-control flexdir'>"
    + "<option value='row'>Row</option>"
    + "<option value='row-reverse'>Row Reverse</option>"
    + "<option value='column'>Column</option>"
    + "<option value='column-reverse'>Column Reverse</option></select></br>"
    + "<label>Flex Wrap:</label> &nbsp;<select name='flexwrap' class='form-control flexwrap'>"
    + "<option value='wrap'>Wrap</option>"
    + "<option value='nowrap'>No Wrap</option>"
    + "<option value='wrap-reverse'>Wrap Reverse</option></select></br>"
    + "<label>Justify Content:</label> &nbsp;<select name='flexcontent' class='form-control flexcontent'>"
    + "<option value='flex-start'>Flex Start</option>"
    + "<option value='flex-end'>Flex End</option>"
    + "<option value='center'>Center</option>"
    + "<option value='space-between'>Space Between</option>"
    + "<option value='space-around'>Space Around</option></select></br>"
    + "<label>Align Items:</label> &nbsp;<select name='flexalign' class='form-control flexalign'>"
    + "<option value='flex-start'>Flex Start</option>"
    + "<option value='flex-end'>Flex End</option>"
    + "<option value='baseline'>Baseline</option>"
    + "<option value='stretch'>Stretch</option></select></br>";

function Flex(headText, nameSelector, selector) {
    var arrItems = [];
    arrItems.push("Generate" + headText + "CSS");
    arrItems.push(nameSelector);
    arrItems.push(selector);
    arrItems.push(typeFunctionalsFlex);
    createFlex(arrItems);
}

function FlexTextarea() {
    var arr = [];
    arr.push("display: " + $(".flex").val() + ";");
    arr.push("flex-direction: " + $(".flexdir").val() + ";");
    arr.push("flex-wrap: " + $(".flexwrap").val() + ";");
    arr.push("justify-content: " + $(".flexcontent").val() + ";");
    arr.push("align-items: " + $(".flexalign").val() + ";");
    return arr;
}

var FlexPreview = function () {
    var preview;
    preview = $("#preview").css({
        "display": $(".flex").val(), "justify-content": $(".flexdir").val(), "flex-direction": $(".flexdir").val(),
        "flex-wrap": $(".flexwrap").val(), "justify-content": $(".flexcontent").val(), "align-items": $(".flexalign").val()
    });
    return preview;
}

var PreviewAreaFlex = function () {
    $('#preview').remove();
    var preview = $(".form-group").append("<div id='preview'><div>1</div><div>2</div><div>3</div></div>")
        + $("#preview").css('display', 'block') +
        FlexPreview();
    $("#preview").css({ "width": "95%", "height": "190px", "padding-top": "0px", "border": "1px solid", "border-radius": "5px" });
    return preview;
}

function createFlex(arrItems) {
    $('.modal-backdrop').css('display', 'block');
    $('.form-inline').css('display', 'block');
    $(".form-group").empty();
    $('.modal-head-h3').empty();
    $('.modal-head-h3').append(arrItems.shift());
    $(".form-group").append(arrItems);
    $("body").toggleClass("dialogIsOpen");
    $(".form-group").change(onSmthFlex).keyup(onSmthFlex);
}
function onSmthFlex() {
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
    var TextareaChange = FlexTextarea();
    for (var i = 0; i < TextareaChange.length; i++) {
        $('#txtarea').append(TextareaChange[i]);
        $('#txtarea').append(newline);
    }
    if ($(".nameSelector").val() || selector === "all elements") $('#txtarea').append("}");
    PreviewAreaFlex();
}