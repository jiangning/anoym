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
 
class Actions
{
	/**
	 * Save name and description into DB
	 * @param text $name
	 * @param text $desc
	 * @return mix
	 */
	public static function saveNameList($name, $desc)
	{
		$result = '';
		
		if($name == null || $name == '' || $desc == null || $desc == '') {
			$result = MessageManager::getMessage('Name and description field should not be empty',MSG_ERROR);
		}
		
		$name = htmlentities(trim($name),ENT_QUOTES,'UTF-8');
		$desc = htmlentities(trim($desc),ENT_QUOTES,'UTF-8');
		$atime = date('Y-m-d H:i:s');
		
		$query = "INSERT INTO namelist (`name`,`desc`,`atime`) VALUES (?,?,?);";
		
		try {
			Database::Excute($query,$name,$desc,$atime);
			$result = true;
		} catch (Exception $e) {
			$result = MessageManager::getMessage($e->getMessage(),MSG_ERROR);
		}
		
		return $result;
	}
	
	/**
	 * Get searching records
	 * @param string $keywords  Single or multiple words
	 * @return array
	 */
	public static function getRecords($keywords)
	{
		$result = array();
		$where = '';
		$keywords = explode(' ', $keywords);
		
		if(count($keywords)>1) {
			$where = '\'%'.implode('%\' OR `name` LIKE \'%', $keywords).'%\'';
		} else {
			$where = '\'%'.$keywords[0].'%\'';
		}
		
		$query = "SELECT * FROM namelist WHERE (`name` LIKE $where) ORDER BY atime DESC;";
		$result = Database::Query($query);
		
		return $result;
	}
	
	/**
	 * Get single notes id
	 * @param int $notesId
	 * @return array
	 */
	public static function getNotes($notesId)
	{
		$result = array();
		
		$query = "SELECT * FROM namelist WHERE id = ?;";
		$result = Database::Query($query,$notesId);
		
		return $result[0];
	}
	
	/**
	 * Get related comments by notes id
	 * @param int $notesId
	 * @return array
	 */
	public static function getComments($notesId)
	{
		$result = array();
		
		$query = "SELECT * FROM comments WHERE notes_id = ? ORDER BY ctime DESC;";
		$result = Database::Query($query,$notesId);
		
		return $result;
	}
	
	/**
	 * Add new comments by notes id
	 * @param int $notesId
	 * @param string $comments
	 * @return mix
	 */
	public static function addComments($notesId,$comments)
	{
		$result = '';
		
		if($notesId == null || $notesId == '' || !is_numeric($notesId)) {
			$result = MessageManager::getMessage('Save comments failed, related notes ID not found.',MSG_ERROR);
		}
		
		if($comments == null || $comments == '') {
			$result = MessageManager::getMessage('Save comments error, comments are empty.',MSG_ERROR);
		}
		
		$comments = htmlentities(trim($comments),ENT_QUOTES,'UTF-8');
		$ctime = date('Y-m-d H:i:s');
		
		$query = "INSERT INTO comments (`notes_id`,`comments`,`ctime`) VALUES (?,?,?);";
		
		try {
			Database::Excute($query,$notesId,$comments,$ctime);
			$result = true;
		} catch (Exception $e) {
			$result = MessageManager::getMessage($e->getMessage(),MSG_ERROR);
		}
		
		return $result;
	}
}

?>
