"use strict";
var typeFunctionalsMultipleColumns = "<label>Number of Columns</label> &nbsp;<input class='form-control num_col' type='number' value='0'></input></br>"
    + "<label>Column Gap</label> &nbsp;<input class='form-control column_gap' type='number' value='0'></input>&nbsp; px</br>";
function MultipleColumns(headText, nameSelector, selector) {
    var arrItems = [];
    arrItems.push("Generate" + headText + "CSS");
    arrItems.push(nameSelector);
    arrItems.push(selector);
    arrItems.push(typeFunctionalsMultipleColumns);
    createMultipleColumns(arrItems);
}
function MultipleColumnsTextarea() {
    var arr = [];
    arr.push("-webkit-column-count:" + $(".num_col").val() + ';');
    arr.push("-webkit-column-gap:" + $('.column_gap').val() + ' px;');
    arr.push("column-count:" + $(".num_col").val() + ';');
    arr.push("column-gap:" + $('.column_gap').val() + ' px;');
    return arr;
}
var MultipleColumnsPreview = function () {
    var preview = $("#preview").css({ "column-count": $(".num_col").val(), "column-gap": $(".column_gap").val() + "px" });
    return preview;
}
var PreviewAreaMultipleColumns = function () {
    $('#preview').remove();
    var preview = $(".form-group").append("<div id='preview'><p>Tolerably earnestly middleton extremely distrusts she boy now not."
        + "Add and offered prepare how cordial two promise. Greatly who affixed suppose but enquire compact prepare all put."
        + "Added forth chief trees but rooms think may. Wicket do manner others seemed enable rather in."
        + "Excellent own discovery unfeeling sweetness questions the gentleman."
        + "Chapter shyness matters mr parlors if mention thought.</p> </div>")
        + $("#preview").css('display', 'block') +
        MultipleColumnsPreview();
    $("#preview").css({ "width": "95%", "border": "none", "font-size": "14px" });
    return preview;
}
function createMultipleColumns(arrItems) {
    $('.modal-backdrop').css('display', 'block');
    $('.form-inline').css('display', 'block');
    $(".form-group").empty();
    $('.modal-head-h3').empty();
    $('.modal-head-h3').append(arrItems.shift());
    $(".form-group").append(arrItems);
    $("body").toggleClass("dialogIsOpen");
    $(".form-group").change(onSmthMultipleColumns).keyup(onSmthMultipleColumns);
}
function onSmthMultipleColumns() {
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
    var TextareaChange = MultipleColumnsTextarea();
    for (var i = 0; i < TextareaChange.length; i++) {
        $('#txtarea').append(TextareaChange[i]);
        $('#txtarea').append(newline);
    }
    if ($(".nameSelector").val() || selector === "all elements") $('#txtarea').append("}");
    PreviewAreaMultipleColumns();
}
