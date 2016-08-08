<?php
namespace Zinc\Components;

class Point {
    // Storage for coordinates
    private $m_indexes = array();
    
    public function __construct(array $indexes) {
        $this->m_indexes = $indexes;
    }
    
    public function __toString() {
        $string = "(";
        
        for ($i = 0; $i < $this->dimension() - 1; ++$i) {
            $string .= $this->index($i).", ";
        }
        
        $string .= $this->index($this->dimension() - 1).")";
        
        return $string;
    }
    
    // Subtract a point from this point
    public function sub(Point $p) {
        $indexes = $this->m_indexes;
        
        // There is a way to do this with an array function,
        // but I'll leave that for another day.
        for ($i = 0; $i < $this->dimension(); ++$i)
            $indexes[$i] -= $p->index($i);
        
        return new Point($indexes);
    }
    
    // Add a point to this point
    public function add(Point $p) {
        $indexes = $this->m_indexes;
    
        for ($i = 0; $i < $this->dimension(); ++$i)
            $indexes[$i] += $p->index($i);
    
        return new Point($indexes);
    }
    
    // Return number of stored coordinates
    public function dimension() {
        return count($this->m_indexes);
    }
    
    // Return coordinate by index
    public function index($i) {
        return $this->m_indexes[$i];
    }
    
    // Set coordinate at index
    public function setIndex($i, $value) {
        $this->m_indexes[$i] = $value;
    }
    
    // Return string format of point
    public function format() {
        return "$this";
    }
}
?>