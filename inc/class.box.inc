/**
 * The MIT License (MIT)
 * 
 * Copyright (c) 2013 Jiang Ning
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
 
<?php 

class Box
{
	public static function getBoxHTML()
	{
		$html = <<<BOX
	<div id="info"></div>
	<div id="addnew">
		<form id="aform" name="aform" method="post" action="index.php">
			<label for="field_name">Subject:</label>
			<input id="field_name" name="field_name" type="text" maxlength="255" required="required" />
			<label for="field_desc">Contents:</label>
			<textarea id="field_desc" name="field_desc" maxlength="5000" required="required"></textarea>
			<div class="field_submit">
				<div class="label_info"></div>
				<span class="label_authcode">Auth Code:</span>
				<img class="authcode" src="/inc/class.authcode.php" onclick="reloadAuthcode()" />
				<input class="field_authcode" name="field_authcode" type="text" maxlength="4" />
				<a id="add" name="add" class="button" href="#">Add</a>
			</div>
		</form>
	</div>
BOX;
	
		return $html;
	}
	
	public static function getBoxJS()
	{
		$js = <<<JS
	<script type="text/javascript">
	
		$(document).ready(function(){
			$("#write").fancybox({
				'title' : null,
				helpers : {
					overlay : {
						css : {
							'background' : 'rgba(0, 0, 0, 0.2)'
						}
					}
				},
				'afterClose':function(){
					$('#info').hide();
					$('#addnew').show();
					$('#field_name').val('');
					$('#field_desc').val('');
					$('.field_authcode').val('');
					$('.label_info').html('');
				}
			});
			$('#add').click(function(){
				if(validation()){
					
					$('#addnew').hide();
					$('#info').show();
					var name = $('#field_name').val();
					var desc = $('#field_desc').val();
					var authcode = $('.field_authcode').val();
					$('#info').html('<img id="loader" src="/templates/images/ajax-loader.gif" />Saving');
					$.ajax({
						url: '/xmlhttprequest/addname.php',
						type: 'POST',
						data: 'name='+name+'&desc='+desc+'&authcode='+authcode,
						dataType: 'html',
						timeout: 6000,
						success: function(html){
							if(html=='incorrect_authcode'){
								$('#info').hide();
								$('#addnew').show();
								$('.label_info').html('Incorrect auth code, please retry.');
							} else {
								$('#info').html(html);
							}
						}
					});
				
				}
			});
		});
		
		function validation(){
			if($('#field_name').val().trim()==''){
				$('.label_info').html('Please enter the name.');
				return false;
			}
			if($('#field_desc').val().trim()==''){
				$('.label_info').html('Please enter the description.');
				return false;
			}
			if($('.field_authcode').val().trim()==''){
				$('.label_info').html('Please enter the authentication code.');
				return false;
			}
			return true;
		}
		
		function reloadAuthcode(){
			$('.authcode').attr('src','/inc/class.authcode.php?'+Math.random());
		}
		
	</script>
JS;

		return $js;
	}
}

?>
