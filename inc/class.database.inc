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
 
require_once $_SERVER['DOCUMENT_ROOT'].'/config/live.inc';

class Database
{
	private static $instance = NULL;
	
	public static function getInstance()
	{
		if(self::$instance === NULL)
		{
			try {
				self::$instance = new PDO('mysql:host='.DB_HOSTNAME.';dbname='.DB_DBNAME,DB_USER,DB_PASSWORD);
				self::$instance->exec("SET NAMES 'utf8';");
			} catch(PDOException $e) {
				echo $e->getMessage();
			}
		}
		
		return self::$instance;
	}
	
	/**
	 * 
	 * @param string $query
	 * @return array
	 */
	public static function Query($query)
	{
		if(self::getInstance()) {
			$rs = self::$instance->prepare($query);
			$rs->setFetchMode(PDO::FETCH_ASSOC);

			$args = func_get_args();
			array_shift($args);
			$rs->execute($args);
			
			return $rs->fetchAll();
		} else {
			return array();
		}
		
	}
	
	/**
	 * 
	 * @param string $query
	 * @return int
	 */
	public static function Excute($query)
	{
		if(self::getInstance()) {
			$rs = self::$instance->prepare($query);
			
			$args = func_get_args();
			array_shift($args);
			
			return $rs->execute($args);
		} else {
			return false;
		}
		
	}

}

?>
