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
 
require_once $_SERVER['DOCUMENT_ROOT'].'/inc/class.frame.inc';

class Render
{
	public $frame;
	public $contents;

	/**
	 * Set contents for main container
	 * @param string $html
	 * @param int $frame
	 * @return void
	 */
	public function __construct($html,$frame=FRAME_HOME)
	{
		$this->frame = new Frame($frame);
		$this->contents = $html;
	}

	function __destruct()
	{
		unset($this->frame);
		unset($this->contents);
	}

	/**
	 * Print page with contents and frame
	 * @return HTML
	 */
	public function getHTML()
	{
		$html = str_replace('###contents###', $this->contents, $this->frame->getFrame());
		
		return $html;
	}
	
}

?>
