"use strict";
var typeFunctionalsTransition="<label>Property</label> &nbsp;<select name='property' class='form-control property'>"
+ "<option value='all'>All</option>"
+ "<option value='background'>Background</option>"
+ "<option value='color'>Color</option>"
+ "<option value='height'>Height</option>"
+ "<option value='width'>Width</option>"
+ "<option value='outline'>Outline</option></select></br>"
+ "<label>Duration</label> &nbsp;<input class='form-control duration' type='number' value='0'></input>&nbsp; </br>"
+ "<label>Unit</label> &nbsp;<select name='time' class='form-control time'>"
+ "<option value='s'>Seconds</option>"
+ "<option value='ms'>Milliseconds</option></select></br>"
+ "<label>Function</label> &nbsp;<select name='function' class='form-control function'>"
+ "<option value='ease'>Ease</option>"
+ "<option value='linear'>Linear</option>"
+ "<option value='ease-in'>Ease-In</option>"
+ "<option value='ease-out'>Ease-Out</option>"
+ "<option value='ease-in-out'>Ease-In-Out</option></select></br>";

function Transition(headText,nameSelector,selector){
    var arrItems=[];
    arrItems.push("Generate"+headText+"CSS");
    arrItems.push(nameSelector);
    arrItems.push(selector);
    arrItems.push(typeFunctionalsTransition);
    createTransition(arrItems);
}

function TransitionTextArea(){
    var arr=[];
    arr.push("-webkit-transition:" + $(".property").val() + " " + $(".duration").val()
    + $(".time").val() + " " + $(".function").val() + ";");
    arr.push("-moz-transition:" + $(".property").val() + " " + $(".duration").val()
    + $(".time").val() + " " + $(".function").val() + ";");
    arr.push("-ms-transition:" + $(".property").val() + " " + $(".duration").val()
    + $(".time").val() + " " + $(".function").val() + ";");
    arr.push("-o-transition:" + $(".property").val() + " " + $(".duration").val()
    + $(".time").val() + " " + $(".function").val() + ";");
    arr.push("transition:" + $(".property").val() + " " + $(".duration").val()
    + $(".time").val() + " " + $(".function").val() + ";");

    return arr;
}
var TransitionPreview=function(){
    if($(".property").val()=="all"){
        var preview = $("#preview").hover(function () {
            $(this).css("background-color", "black");
            $(this).css("color", "white");
            $(this).css("height", "250px");
            $(this).css("width", "250px");
            $(this).css("outline", "#ff1b1b dotted 5px");
            $(this).css('transition', $('.property').val() + " " + $('.duration').val() + $('.time').val()+" " + $('.function').val());
            }, function () {
                $(this).attr('style', 'outline:#ff1b1b dotted 0px');
                $(this).css('display', 'block');
                 $(this).css({"transition": "all "+ $('.duration').val()+$(".time").val()+" "+$(".function").val()});
            });
    }
    else if($(".property").val()=="background"){
        var preview=$("#preview").hover(function(){
            $(this).css("background-color", "black");
            $(this).css('transition', $('.property').val() + " " + $('.duration').val() + $('.time').val()+ " " + $('.function').val());
        }, function(){
            $(this).attr('style', '');
                $(this).css('display', 'block');
                $(this).css({"transition": "background "+ $('.duration').val()+$(".time").val()+" "+$(".function").val()});
        });
    }
    else if($(".property").val()=="color"){
        var preview=$("#preview").hover(function(){
            $(this).css("color", "blue");
            $(this).css('transition', $('.property').val() + " " + $('.duration').val() + $('.time').val()+" " + $('.function').val());
        }, function(){
            $(this).attr('style', '');
                $(this).css('display', 'block');
                $(this).css({"transition": "color "+ $('.duration').val()+$(".time").val()+" "+$(".function").val()});
        });
    }
    else if($(".property").val()=="height"){
        var preview=$("#preview").hover(function(){
            $(this).css("height", "250px");
            $(this).css('transition', $('.property').val() + " " + $('.duration').val() + $('.time').val()+ " " + $('.function').val());
        }, function(){
            $(this).attr('style', '');
                $(this).css('display', 'block');
                $(this).css({"transition": "height "+ $('.duration').val() + $('.time').val()+" "+$(".function").val()});
        });
    }
    else if($(".property").val()=="width"){
        var preview=$("#preview").hover(function(){
            $(this).css("width", "250px");
            $(this).css('transition', $('.property').val() + " " + $('.duration').val() + $('.time').val()+ " " + $('.function').val());
        }, function(){
            $(this).attr('style', '');
                $(this).css('display', 'block');
                $(this).css({"transition": "width "+ $('.duration').val() + $('.time').val()+" "+$(".function").val()});
        });
    }
    else if($(".property").val()=="outline"){
        var preview=$("#preview").hover(function(){
            $(this).css("outline", "#ff1b1b dotted 5px");
             $(this).css('transition', $('.property').val() + " " + $('.duration').val() + $('.time').val()+ " " + $('.function').val());
        }, function(){
            $(this).attr('style', 'outline:#ff1b1b dotted 0px');
                $(this).css('display', 'block');
                $(this).css({"transition": "outline "+ $('.duration').val() + $('.time').val()+" "+$(".function").val()});
        });
    }
    return preview;
}
var previewAreaTransition=function(){
      $('#preview').remove();
        var preview=$(".form-group").append("<div id='preview'>Hover me!</div>")
        +$("#preview").css('display', 'block')
        +TransitionPreview();
    return preview;
}
function createTransition(arrItems){
    $('.modal-backdrop').css('display','block');
    $(".form-inline").css('display','block');
    $(".form-group").empty();
    $('.modal-head-h3').empty();
    $('.modal-head-h3').append(arrItems.shift());
    $(".form-group").append(arrItems);
    $("body").toggleClass("dialogIsOpen");
    $(".form-group").change(onSmthTransition).keyup(onSmthTransition);
}
function onSmthTransition(){
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
    var TextareaChange=TransitionTextArea();
    for (var i = 0; i <TextareaChange.length; i++) {
        $('#txtarea').append(TextareaChange[i]);
        $('#txtarea').append(newline);
    }
    if($(".nameSelector").val()||selector==="all elements")$('#txtarea').append("}");
    previewAreaTransition();
}
