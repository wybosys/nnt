<?php

require_once "server/lib/JSON.phps";

class class_viewboard extends ServiceIntrospection {
	
	function method_query_digital($params, $error) {
		$ret = array(
                     'col' => array('sku', 'name', 'color', 'comment'),
                     'rows' => array(
                                     array("210210", '大衣', '白色', 'test'),
                                     array("213212", '长裤', '黑色', 'test'),
                                     array("210210", '大衣', '白色', 'test'),
                                     array("213212", '长裤', '黑色', 'test'),
                                     array("210210", '大衣', '白色', 'test'),
                                     array("213212", '长裤', '黑色', 'test'),
                                     array("210210", '大衣', '白色', 'test'),
                                     array("213212", '长裤', '黑色', 'test'),
                                     array("213212", '长裤', '黑色', 'test')
                                     ),
                     'all_records' => 20
		);
		return $ret;
	}

    function method_query_graph($params, $error) {
        $ret = array(
                     array('白色', 0xffffffff, 100),
                     array('红色', 0xff0000ff, 200),
                     array('绿色', 0x00ff00ff, 300),
		     array('蓝色', 0x0000ffff, 150),
		     array('白色', 0xffffffff, 120),
                     array('红色', 0xff0000ff, 50),
                     array('绿色', 0x00ff00ff, 350),
		     array('蓝色', 0x0000ffff, 180)
                     );
        return $ret;
    }
	
	function method_count($params, $error) {
		return 50;
	}
	
}

?>