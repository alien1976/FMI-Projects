var textareaBoxResizing="<textarea id='txtarea' row='10' cols='50' disabled></textarea>";
var typeFunctionalsBoxResizing=
"<label>Box Resizing:</label> &nbsp;<select name='resizing' class='resizing'>"
+"<option value='none'>None</option>"
+"<option value='both'>Both</option>"
+"<option value='horizontal'>Horizontal</option>"
+"<option value='vertical'>Vertical</option>"
+"<option value='initial'>Initial</option>"
+"<option value='inherit'>Inherit</option></select></br>";

function BoxResizing(headText,nameSelector,selector){
    var arrItems=[];
        arrItems.push("Generate"+headText+"CSS");
        arrItems.push(nameSelector);
        arrItems.push(selector);
        arrItems.push(typeFunctionalsBoxResizing);
        arrItems.push(textareaBoxResizing);
        createBoxShadow(arrItems);
}

function BoxResizingTextarea(){
    var arr=[];
    arr.push("resize:"+$(".resizing").val()+";");
    return arr;
}

var BoxResizingPreview=function(){
    var preview;
    preview=$("#preview").css({"resize":$(".resizing").val(),"overflow":"auto"});
    return preview;
}

var PreviewAreaBoxResizing=function(){
    $('#preview').remove();
        var preview=$(".modelContentBody").append("<div id='preview'>Pull the bottom right corner!</div>")
        +$("#preview").css('display', 'block')+
        BoxResizingPreview();
        return preview;
}

function createBoxShadow(arrItems){
        $('.modal-backdrop').css('display','block');
        $('#modal-container').css('display','block');
        $(".modelContentBody").empty();
        $('.modal-head-h3').empty();
        $('.modal-head-h3').append(arrItems.shift());
        $(".modelContentBody").append(arrItems);
        $("body").toggleClass("dialogIsOpen");
        $(".modelContentBody").change(onSmthBoxResizing).keyup(onSmthBoxResizing);   
    }
    function onSmthBoxResizing(){
        $('#txtarea').empty();
        var newline = String.fromCharCode(13, 10);
        var selector=$(".selector").val();
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
        }else if(selector==="all elements"){
            $('#txtarea').append("* {");
            $('#txtarea').append(newline);
        }
        var TextareaChange=BoxResizingTextarea();
        for (var i = 0; i <TextareaChange.length; i++) {
           $('#txtarea').append(TextareaChange[i]);
           $('#txtarea').append(newline);
        }
        if($(".nameSelector").val()||selector==="all elements")$('#txtarea').append("}");
        PreviewAreaBoxResizing();
    }