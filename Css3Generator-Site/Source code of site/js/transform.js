"use strict";
var typeFunctionalsTransform="<label>Scale:</label> &nbsp;<input class='form-control scale' type='number' value='0'></input></br>"
+"<label>Rotate:</label> &nbsp;<input class='form-control rotate' type='number' value='0'></input></br>"
+"<label>Translate X:</label> &nbsp;<input class='form-control transX' type='number' value='0'></input></br>"
+"<label>Translate Y:</label> &nbsp;<input class='form-control transY' type='number' value='0'></input></br>"
+"<label>Skew X:</label> &nbsp;<input class='form-control skewX' type='number' value='0'></input></br>"
+"<label>Skew Y:</label> &nbsp;<input class='form-control skewY' type='number' value='0'></input></br>";


function Transform(headText,nameSelector,selector){
    var arrItems=[];
    arrItems.push("Generate"+headText+"CSS");
    arrItems.push(nameSelector);
    arrItems.push(selector);
    arrItems.push(typeFunctionalsTransform);
    createTransform(arrItems);
}

function TransformTextArea(){
    var arr=[];
    arr.push("-moz-transform:"+"scale("+$(".scale").val()+") rotate("+$(".rotate").val()+"deg) translateX("+$(".transX").val()+"px) translateY("+$(".transY").val()+"px) skewX("
    +$(".skewX").val()+"deg) skewY("+$(".skewY").val()+"deg);");
    arr.push("-webkit-transform:"+"scale("+$(".scale").val()+") rotate("+$(".rotate").val()+"deg) translateX("+$(".transX").val()+"px) translateY("+$(".transY").val()+"px) skewX("
    +$(".skewX").val()+"deg) skewY("+$(".skewY").val()+"deg);");
    arr.push("-o-transform:"+"scale("+$(".scale").val()+") rotate("+$(".rotate").val()+"deg) translateX("+$(".transX").val()+"px) translateY("+$(".transY").val()+"px) skewX("
    +$(".skewX").val()+"deg) skewY("+$(".skewY").val()+"deg);");
    arr.push("-ms-transform:"+"scale("+$(".scale").val()+") rotate("+$(".rotate").val()+"deg) translateX("+$(".transX").val()+"px) translateY("+$(".transY").val()+"px) skewX("
    +$(".skewX").val()+"deg) skewY("+$(".skewY").val()+"deg);");
    arr.push("transform:"+"scale("+$(".scale").val()+") rotate("+$(".rotate").val()+"deg) translateX("+$(".transX").val()+"px) translateY("+$(".transY").val()+"px) skewX("
    +$(".skewX").val()+"deg) skewY("+$(".skewY").val()+"deg);");
    return arr;
}

var TransformPreview=function(){
    var preview=$("#preview").css({"-moz-transform":"scale("+$(".scale").val()+") rotate("+$(".rotate").val()+"deg) translateX("+$(".transX").val()+"px) translateY("+$(".transY").val()+"px) skewX("
    +$(".skewX").val()+"deg) skewY("+$(".skewY").val()+"deg)","-webkit-transform":"scale("+$(".scale").val()+") rotate("+$(".rotate").val()+"deg) translateX("+$(".transX").val()+"px) translateY("+$(".transY").val()+"px) skewX("
    +$(".skewX").val()+"deg) skewY("+$(".skewY").val()+"deg)","-o-transform":"scale("+$(".scale").val()+") rotate("+$(".rotate").val()+"deg) translateX("+$(".transX").val()+"px) translateY("+$(".transY").val()+"px) skewX("
    +$(".skewX").val()+"deg) skewY("+$(".skewY").val()+"deg)","-ms-transform":"scale("+$(".scale").val()+") rotate("+$(".rotate").val()+"deg) translateX("+$(".transX").val()+"px) translateY("+$(".transY").val()+"px) skewX("
    +$(".skewX").val()+"deg) skewY("+$(".skewY").val()+"deg)","transform":"scale("+$(".scale").val()+") rotate("+$(".rotate").val()+"deg) translateX("+$(".transX").val()+"px) translateY("+$(".transY").val()+"px) skewX("
    +$(".skewX").val()+"deg) skewY("+$(".skewY").val()+"deg)"})
    return preview;
}

var previewAreaTransform=function(){
     $('#preview').remove();
    var preview=$(".form-group").append("<div id='preview'></div>")
    +$("#preview").css('display', 'block');
    TransformPreview();
    return preview;
}

function createTransform(arrItems){
    $('.modal-backdrop').css('display','block');
    $(".form-inline").css('display','block');
    $(".form-group").empty();
    $('.modal-head-h3').empty();
    $('.modal-head-h3').append(arrItems.shift());
    $(".form-group").append(arrItems);
    $("body").toggleClass("dialogIsOpen");
    $(".form-group").change(onSmthTransform).keyup(onSmthTransform);
}

function onSmthTransform(){
    $('#txtarea').empty();
    var newline = String.fromCharCode(13,10);
    var selector = $(".selector").val();
    if($(".nameSelector").val()){
        switch(selector)
        {
            case "id":$('#txtarea').append("#"+$(".nameSelector").val());break;
            case "class":$('#txtarea').append("."+$(".nameSelector").val());break;
            case "element":$('#txtarea').append($(".nameSelector").val());break;
            case"all elements":$('#txtarea').append("*");break;
        }
        $('#txtarea').append(" {");
        $('#txtarea').append(newline);
    }
    else if(selector==="all elements"){
        $('#txtarea').append("* {");
        $('#txtarea').append(newline);
    }
    var TextareaChange=TransformTextArea();
    for (var i = 0; i <TextareaChange.length; i++) {
        $('#txtarea').append(TextareaChange[i]);
        $('#txtarea').append(newline);
    }
    if($(".nameSelector").val()||selector==="all elements")$('#txtarea').append("}");
    previewAreaTransform();
}
