<?php
namespace Zinc\Components;

abstract class CubieType extends \Zinc\BasicEnum {
    const KEY = 0;
    const EDGE = 1;
    const CORNER = 2;
}

class Cubie {
    // Storage for number of faces on cubie
    private $m_faces = 1;
    
    // Storage for type of cubie
    private $m_type = CubieType::KEY;
    
    // Storage for cubie value
    private $m_value;
    
    public function __construct($value) {
        $this->m_value = $value;
    }
    
    // Return cubie value
    public function value() {
        return $this->m_value;
    }
}
?>