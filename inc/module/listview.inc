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
require_once $_SERVER['DOCUMENT_ROOT'].'/inc/class.render.inc';
require_once $_SERVER['DOCUMENT_ROOT'].'/inc/class.box.inc';
require_once $_SERVER['DOCUMENT_ROOT'].'/inc/class.datastructure.inc';
require_once $_SERVER['DOCUMENT_ROOT'].'/inc/class.actions.inc';

class Listview
{
	public $listview;
	
	/**
	 * @param string $request  GET(detailview) or POST(listview)
	 */
	public function __construct($request)
	{
		$this->listview = new Render($this->getContents($request),FRAME_LIST);
	}

	public function getHTML()
	{
		return $this->listview->getHTML();
	}

	/**
	 * Get HTML contents for main container
	 * @param string $request  GET(detailview) or POST(listview)
	 */
	public function getContents($request)
	{
		$html = <<<LISTVIEW
	<div id="headmaster">
		<a id="title" href="index.php">Anoym</a>
		<form name="sform" method="post" action="list.php">
			<input id="namefield" name="namefield" type="text" maxlength="255" />
			<a id="search" name="search" class="button" href="javascript:submit();">Search</a>
		</form>
		<a id="write" name="write" class="book" href="#box" title="Add new"></a>
	</div>
	<div id="box">
LISTVIEW;
		$html .= Box::getBoxHTML();
		$html .= '
	</div>';
		$html .= Box::getBoxJS();
		
		//see hp.inc
		$html .= <<<JS
	<script type="text/javascript">
		function submit(){
			if(sform_validation()){
				document.sform.submit();
			}
		}
		function sform_validation(){
			if($('#namefield').val().trim()==''){
				return false;
			} else {
				return true;
			}
		}
	</script>
JS;
		
		$html .= '<div class="wrap">'; //wrap start
		
		//if list results
		if(!empty($_POST['namefield'])) {
			$keywords = trim($_POST['namefield']);
			$records = Actions::getRecords($keywords);
			$count = count($records);
			
			//echo results
			if($count > 0) {
				if($count == 1) {
					$html .= "<p class='record_count'>There is one note found.</p>";
				} else {
					$html .= "<p class='record_count'>There are <em>$count</em> notes found.</p>";
				}
				
				foreach($records as $record) {
					$html .= '<div class="record">';
					$html .= '<a class="record_name" href="/list.php?id='.$record['id'].'" target="_blank">'.$record['name'].'</a>';
					$html .= '<p class="record_desc">'.$record['desc'].'</p>';
					$html .= '<p class="record_date">'.$record['atime'].'</p>';
					$html .= '</div>';
				}
			} else {
				$html .= '<div class="record_notfound">Opps, nothing found.</div>';
			}
		}
		
		//if view details
		if(!empty($_GET['id'])) {
			$id = $_GET['id'];
			
			$notes = Actions::getNotes($id);
			
			if(empty($notes) || $notes == null) {
				$html .= '<div class="record_notfound">Opps, nothing found.</div>';
				return $html;
			}
			
			$html .= '<div class="wrap_details">';
			
			$html .= '<p class="notes_name">'.$notes['name'].'</p>';
			$html .= '<p class="notes_date">'.$notes['atime'].'</p>';
			$html .= '<p class="notes_desc">'.$notes['desc'].'</p>';
			
			$html .= <<<COMMENTSBOX
	<div class="commentsbox">
		<a class="comments_title" href="javascript:commentsboxtoggle();">Add comments</a>
		<div id="comments_info"></div>
		<div id="comments_addnew">
			<textarea id="comments_contents" name="comments_contents" maxlength="1000"></textarea>
			<div class="field_submit">
				<div class="label_info"></div>
				<span class="label_authcode">Auth Code:</span>
				<img class="authcode" src="/inc/class.authcode.php" onclick="reloadAuthcode()" />
				<input id="comments_field_authcode" name="field_authcode" type="text" maxlength="4" />
				<a id="comments_submit" name="submit" class="button" href="#">Submit</a>
				<div class="clear"></div>
			</div>
		</div>
	</div>
	<script type="text/javascript">
	
		$('#comments_submit').click(function(){
			if(validation_comments()){
				
				$('#comments_addnew').hide();
				$('#comments_info').show();
				var comments = $('#comments_contents').val();
				var authcode = $('#comments_field_authcode').val();
				$('#comments_info').html('<img class="loader" src="/templates/images/ajax-loader.gif" />Saving');
				$.ajax({
					url: '/xmlhttprequest/addcomments.php',
					type: 'POST',
					data: 'notesId='+$id+'&comments='+comments+'&authcode='+authcode,
					dataType: 'html',
					timeout: 6000,
					success: function(html){
						if(html=='incorrect_authcode'){
							$('#comments_info').hide();
							$('#comments_addnew').show();
							$('.label_info').html('Incorrect auth code, please retry.');
						} else {
							$('#comments_info').html(html);
						}
					}
				});
			
			}
		});
		
		function validation_comments(){
			if($('#comments_contents').val().trim()==''){
				$('.label_info').html('Please enter the comments.');
				return false;
			}
			if($('#comments_field_authcode').val().trim()==''){
				$('.label_info').html('Please enter the authentication code.');
				return false;
			}
			return true;
		}
		
		function commentsboxtoggle(){
			if($('.commentsbox').hasClass("commentsbox_open")){
				$('#comments_addnew').hide();
				$('.commentsbox').removeClass("commentsbox_open");
				$('#comments_info').val('');
				$('#comments_contents').val('');
				$('.label_info').val('');
				$('#comments_field_authcode').val('');
				$('#comments_info').html('');
				reloadAuthcode();
			}else{
				$('#comments_addnew').show();
				$('.commentsbox').addClass("commentsbox_open");
			}
		}
		
	</script>
COMMENTSBOX;
			
			$records = Actions::getComments($id);
			$count = count($records);
			
			//echo results
			if($count > 0) {
				foreach($records as $comments) {
					$html .= '<div class="comments">';
					$html .= '<p class="record_desc">'.$comments['comments'].'</p>';
					$html .= '<p class="record_date">'.$comments['ctime'].'</p>';
					$html .= '</div>';
				}
			}
			
			$html .= '</div>'; //end wrap_details
			
		}
		
		$html .= '</div>'; //wrap end
		
		return $html;
	}
	
}
?>
