<?php
namespace Zinc\Components;

abstract class Rotation extends \Zinc\Lib\BasicEnum {
    const CLOCKWISE         = 0;
    const COUNTER_CLOCKWISE = 1;
    const HALF              = 2;
}

abstract class Axis extends \Zinc\Lib\BasicEnum {
    const HORIZONTAL = 0;
    const VERTICAL   = 1;
}

class Slice {
    // Storage for slice width
    // (all slices in cube should be same width)
    private $m_width;
    
    // Storage for cubies in slice
    private $m_cubies;
    
    public function __construct($values, $width = 0) {
        $this->m_cubies = new CubieMatrix;
        
        if ($values instanceof CubieMatrix) {
            $this->m_width = $values->count();
            $this->m_cubies = $values;
        }
        
        else {
            $this->m_width = $width;
            
            // Split string into rows
            $rows = str_split($values, $width);
            
            // Iterate rows
            foreach ($rows as $rowString) {
                // Add row vector to matrix
                $this->m_cubies[] = new CubieVector(str_split($rowString));
            }
        }
    }
    
    // Return slice width
    public function width() {
        return $this->m_width;
    }
    
    // Return row by index
    public function row($row) {
        return $this->m_cubies[$row];
    }
    
    // Return column by index
    public function column($column) {
        return $this->_transpose($this->m_cubies)[$column];
    }
    
    // Set slice row
    public function setRow(CubieVector $row, $idx) {
        $this->m_cubies[$idx] = $row;
        
        return $this;
    }
    
    // Set slice column
    public function setColumn(CubieVector $column, $idx) {
        $this->m_cubies = $this->_transpose($this->m_cubies);
        $this->m_cubies[$idx] = $column;
        $this->m_cubies = $this->_transpose($this->m_cubies);
    
        return $this;
    }
    
    // Rotate slice
    public function rotate($rot = Rotation::CLOCKWISE) {
        switch ($rot) {
            case Rotation::CLOCKWISE:
                $this->m_cubies = $this->_reverse($this->_transpose($this->m_cubies), Axis::HORIZONTAL);
                
                break;
            case Rotation::COUNTER_CLOCKWISE:
                $this->m_cubies = $this->_reverse($this->_transpose($this->m_cubies), Axis::VERTICAL);
                
                break;
            case Rotation::HALF:
                $this->m_cubies = $this->_reverse($this->_reverse($this->m_cubies, Axis::HORIZONTAL), Axis::VERTICAL);
                
                break;
        }
        
        return $this;
    }
    
    // Return formatted row by index
    public function formatRow($row) {
        $format = "";
        
        // Iterate cubies
        foreach ($this->m_cubies[$row] as $cubie)
            $format .= " $cubie";
        
        return $format;
    }
    
    // Return formatted slice
    public function format() {
        $format = "";
        
        // Iterate rows
        foreach ($this->m_cubies as $index=>$row)
            $format .= $this->formatRow($index).PHP_EOL;
        
        return $format;
    }
    
    // Return slice state
    public function state() {
        $format = "";
        
        // Iterate rows
        foreach ($this->m_cubies as $row)
            $format .= implode($row->getArrayCopy());
        
        return $format;
    }
    
    // Return transposed matrix
    public function _transpose(CubieMatrix $cubies) {
        $transposedCubies = clone $cubies;
        
        for ($i = 0; $i < count($cubies); ++$i)
            for ($j = 0; $j < count($cubies[$i]); ++$j)
                $transposedCubies[$j][$i] = $cubies[$i][$j];
        
        return $transposedCubies;
    }
    
    // Return reversed (axis-flipped) matrix
    public function _reverse(CubieMatrix $cubies, $axis) {
        $width = count($cubies);
        $reversedCubies = clone $cubies;
        
        switch ($axis) {
            case Axis::HORIZONTAL:
                for ($i = 0; $i < $width; ++$i)
                    for ($j = 0; $j < $width; ++$j)
                        $reversedCubies[$i][$width - $j - 1] = $cubies[$i][$j];
                
                break;
            case Axis::VERTICAL:
                for ($i = 0; $i < $width; ++$i)
                    for ($j = 0; $j < $width; ++$j)
                        $reversedCubies[$width - $i - 1][$j] = $cubies[$i][$j];
                
                break;
        }
        
        return $reversedCubies;
    }
}
?>