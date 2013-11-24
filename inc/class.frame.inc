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
 
require_once $_SERVER['DOCUMENT_ROOT'].'/inc/class.datastructure.inc';

class Frame
{
	public $frame;

	/**
	 * Read template
	 * @param int $frame
	 */
	public function __construct($frame)
	{
		switch ($frame)
		{
			case FRAME_HOME:
				$this->frame = file_get_contents($_SERVER['DOCUMENT_ROOT']."/templates/home.html");
				break;
			case FRAME_LIST:
				$this->frame = file_get_contents($_SERVER['DOCUMENT_ROOT']."/templates/list.html");
				break;
			case FRAME_ADMIN:
				$this->frame = file_get_contents($_SERVER['DOCUMENT_ROOT']."/templates/admin.html");
				break;
			default:
				$this->frame = file_get_contents($_SERVER['DOCUMENT_ROOT']."/templates/home.html");
		}

	}

	/**
	 * Get Header, empty contents area and footer
	 */
	public function getFrame()
	{
		return $this->frame;
	}

}

?>