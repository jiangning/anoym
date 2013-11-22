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
	session_start();
	Header("Content-type: image/PNG");
	$im = imagecreate(50,30);
	$bg = ImageColorAllocate($im, 0,0,0);
	imagefill($im,0,0,$bg);
	$vcodes = "";
	srand((double)microtime()*1000000);
	
	for($i = 0; $i < 4; $i++) {
		$font = ImageColorAllocate($im, 200,200,200);
		$authnum=rand(1,9);
		$vcodes.=$authnum;
		imagestring($im, 16, 6+$i*10, 8, $authnum, $font);
	}

	$_SESSION['VCODE'] = $vcodes;
	
	for($i = 0; $i < 100; $i++) {
		$randcolor = ImageColorallocate($im,rand(0,255),rand(0,255),rand(0,255));
		//imagesetpixel($im, rand()%70 , rand()%30 , $randcolor);
	}
	
	ImagePNG($im);
	ImageDestroy($im);
?>
