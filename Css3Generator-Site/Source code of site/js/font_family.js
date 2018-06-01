"use strict";
var typeFunctionalsFontFamily = "<label>Font Family</label> &nbsp;<input class='form-control fontFamily' type='text' value=''></input></br>"
    + "<label>Font Name</label> &nbsp;<input class='form-control fontName' type='text' value=''></input></br>";
function FontFamily(headText, nameSelector, selector) {
    var arrItems = [];
    arrItems.push("Generate" + headText + "CSS");
    arrItems.push(typeFunctionalsFontFamily);
    createFontFamily(arrItems);
}
function FontFamilyTextarea() {
    var arr = [];
    arr.push("  font-family:" + ' "' + $(".fontFamily").val() + '";');
    arr.push("  src:" + ' url("' + $('.fontName').val() + '.eot?")' + ' format("eot"),');
    arr.push("  column-count:" + ' url("' + $('.fontName').val() + '.woff")' + ' format("woff"),');
    arr.push("  column-gap:" + ' url("' + $('.fontName').val() + '.ttf")' + ' format("truetype");');
    return arr;
}
var FontFamilyPreview = function () {
    var preview = $("#preview").css({ "column-count": $(".num_col").val(), "column-gap": $(".column_gap").val() + "px" });
    return preview;
}
var PreviewAreaFontFamily = function () {
    $('#preview').remove();
    var preview = $(".form-group").append("<div id='preview'>Tolerably earnestly middleton extremely distrusts she boy now not."
        + "Add and offered prepare how cordial two promise. Greatly who affixed suppose but enquire compact prepare all put."
        + "Added forth chief trees but rooms think may. Wicket do manner others seemed enable rather in."
        + "Excellent own discovery unfeeling sweetness questions the gentleman."
        + "Chapter shyness matters mr parlors if mention thought. </div>")
        + $("#preview").css('display', 'block') +
        FontFamilyPreview();
    $('#font').remove();
    $("head").append("<link href='https://fonts.googleapis.com/css?family=" + $(".fontName").val() + "' rel='stylesheet' id='font' />");
    $("#preview").css({ "font-family": $(".fontName").val(), "width": "95%", "height": "240px", "border": "none", "font-size": "14px" });
    return preview;
}
function createFontFamily(arrItems) {
    $('.modal-backdrop').css('display', 'block');
    $('.form-inline').css('display', 'block');
    $(".form-group").empty();
    $('.modal-head-h3').empty();
    $('.modal-head-h3').append(arrItems.shift());
    $(".form-group").append(arrItems);
    $("body").toggleClass("dialogIsOpen");
    $(".form-group").change(onSmthFontFamily).keyup(onSmthFontFamily);
}
function onSmthFontFamily() {
    $('#txtarea').empty();
    var newline = String.fromCharCode(13, 10);
    $('#txtarea').append("@font-face {");
    $('#txtarea').append(newline);
    var TextareaChange = FontFamilyTextarea();
    for (var i = 0; i < TextareaChange.length; i++) {
        $('#txtarea').append(TextareaChange[i]);
        $('#txtarea').append(newline);
    }
    $('#txtarea').append("}");
    PreviewAreaFontFamily();
}
