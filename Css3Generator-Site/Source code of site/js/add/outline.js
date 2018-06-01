var textareaOutline = "<textarea id='txtarea' rows='10' cols='50' disabled></textarea>";
var typeFunctionalOutline=
            "<label>Outline thickness</label> &nbsp;<input class='thickness' type='number' value='0'></input>&nbsp; px</br>"
            +"<label>Outline</label> &nbsp;<select name='outline' class='outline'>"
            +"<option value='dotted'>Dotted</option>"
            +"<option value='dashed'>Dashed</option>"
            +"<option value='solid'>Solid</option>"
            +"<option value='groove'>Groove</option>"
            +"<option value='ridge'>Ridge</option>"
            +"<option value='inset'>Inset</option>"
            +"<option value='outset'>Outset</option>"
            +"<option value='double'>Double</option>"
            +"<option value='auto'>Auto</option></select></br>"
            +"<label>Outline Color</label> &nbsp;<input class='jscolor' value='ab2567'></br>"
            +"<label>Outline Offset</label> &nbsp;<input class='offset' type='number' value='0'></input></br>";

            function Outline(headText,nameSelector,selector){
                var arrItems=[];
                arrItems.push("Generate"+headText+"CSS");
                arrItems.push(nameSelector);
                arrItems.push(selector);
                arrItems.push(typeFunctionalOutline);
                arrItems.push(textareaOutline);
                createOutline(arrItems);
            }

            function OutlineTextarea(){
                var arr=[];
                if($(".jscolor").val()){
                    arr.push("outline: "+$(".thickness").val()+"px "+$(".outline").val()+" "+"#"+$(".jscolor").val()+";");
                }
                else{
                    arr.push("outline: "+$(".thickness").val()+"px "+$(".outline").val()+";");
                }

                if($(".offset").val()){
                    arr.push("outline-offset: "+$(".offset").val()+"px;");
                }

                return arr;
            }

            var OutlinePreview=function(){
                var preview;
                if($(".jscolor").val()){
                    preview=$("#preview").css({"outline": $(".thickness").val()+"px "+$(".outline").val()+" "+"#"+$(".jscolor").val(),
                    "outline-offset": $(".offset").val()+"px"});
                }
                else{
                    preview=$("#preview").css({"outline": $(".thickness").val()+"px "+$(".outline").val(),
                    "outline-offset": $(".offset").val()+"px"});
                }
                return preview;
            }

            var PreviewAreaOutline=function(){
                $('#preview').remove();
                var preview = $(".modelContentBody").append("<div id='preview'></div>")
                +$("#preview").css('display','block')+
                OutlinePreview();
                return preview;
            }
            function createOutline(arrItems){
                $('.modal-backdrop').css('display','block');
                $('#modal-container').css('display','block');
                $('.modelContentBody').empty();
                $('.modal-head-h3').empty();
                $('.modal-head-h3').append(arrItems.shift());
                $('.modelContentBody').append(arrItems);
                jscolor.installByClassName("jscolor");
                $("body").toggleClass("dialogIsOpen");
                $(".modelContentBody").change(onSmthOutline).keyup(onSmthOutline);
            }
            function onSmthOutline(){
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
                else if(selector === "all elements"){
                    $('#txtarea').append("* {");
                    $('#txtarea').append(newline);
                }
            var TextareaChange=OutlineTextarea();
            for(var i=0;i<TextareaChange.length;i++){
                $("#txtarea").append(TextareaChange[i]);
                $("#txtarea").append(newline);
            }
            if($(".nameSelector").val()||selector==="all elements")$("#txtarea").append("#txtarea").append("}");
            PreviewAreaOutline();
            }