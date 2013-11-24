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
require_once $_SERVER['DOCUMENT_ROOT'].'/inc/class.actions.inc';

class xmlhttprequest_AddComments
{
	/**
	 * @param int $notesId
	 * @param string $comments
	 * @param int $authcode
	 * @return HTML
	 */
	public function action($notesId,$comments,$authcode)
	{
		session_start();
		$html = '';
		
		if($authcode == $_SESSION['VCODE']) {
			$result =  Actions::addComments($notesId, $comments);
			
			if($result) {
				$html = MessageManager::getMessage('Your comments has been added.',MSG_SUCCESS);
			} else {
				$html = MessageManager::getMessage('Error occurred during add comments, please retry.',MSG_ERROR);
			}
		} else {
			$html = 'incorrect_authcode';
		}
		
		return $html;
	}
	
}

$response = new xmlhttprequest_AddComments();

echo $response->action($_POST['notesId'],$_POST['comments'],$_POST['authcode']);

?>
