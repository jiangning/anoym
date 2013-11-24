<?php
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

require_once $_SERVER['DOCUMENT_ROOT'].'/inc/class.render.inc';
require_once $_SERVER['DOCUMENT_ROOT'].'/inc/class.box.inc';
require_once $_SERVER['DOCUMENT_ROOT'].'/inc/class.datastructure.inc';

class HP
{
	public $hp;

	public function __construct()
	{
		$this->hp = new Render($this->getContents());
	}

	public function getHTML()
	{
		return $this->hp->getHTML();
	}

	/**
	 * Get HTML contents for main container
	 */
	public function getContents()
	{
		$html = <<<HP
	<div id="logo">
		<div id="title">Anoym</div>
		<a id="write" name="write" class="book" href="#box" title="Add new"></a>
		<div class="clear"></div>
		<div id="subtitle">A note by anonymous</div>
	</div>
	<div id="searchbar">
		<form name="sform" method="post" action="list.php">
			<input id="namefield" name="namefield" type="text" maxlength="255" />
			<a id="search" name="search" class="button" href="javascript:submit();">Search</a>
		</form>
		<div class="clear"></div>
	</div>
	<div id="notify"></div>
	<div id="box">
HP;
		$html .= Box::getBoxHTML();
		$html .= '
	</div>';
		$html .= Box::getBoxJS();
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
		
		return $html;
	}
	
}
?>
