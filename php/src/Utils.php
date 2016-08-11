<?php
namespace Zinc;

class Utils {
    // Interface for forming colored console messages
    private $colors;
    
    public function __construct() {
        $this->colors = new Colors;
    }
    
    // Test console, colored console, and input
    public function consoleTest() {
        // Test output
        echo "this is a console test\n";
        
        // Test colored output
        echo $this->colors->getColoredString("this is a colored console test\n", "red");
        
        // Test input and return
        $input = $this->get_string("this is an input test: ", "light_blue");
        echo "i got $input";
        
        // Test console pause
        $this->console_pause();
        
        // Test menu
        $this->menu("This is a menu!", ["spinach", "barley", "henry viii"], ["A green leafy thing", "Some grain", "A really old kingadoo"]);
        
        // Test error
        $this->error("time to quit!");
    }
    
    // Output a formatted error
    public function error($msg, $fatal = false, $negateFatal = false) {
        // Fatal error
        if ($fatal) {
            $this->alert("FATAL ERROR: $msg , terminating program", "light_red");
            return $negateFatal ? -1 : 0;
        }
        
        // Normal error
        else {
            $this->alert("ERROR: $msg", "light_red");
            return 1;
        }
    }
    
    // Output an emphasized message 
    public function alert($msg, $color = null) {
        echo $this->colors->getColoredString("\n *** $msg\n\n", $color);
    }
    
    // Pause the console until input is received
    public function console_pause() {
        echo "\nPress ENTER to continue...";
        fgetc(STDIN);
    }
    
    // Get string from user
    public function get_string($prompt, $color) {
        echo $this->colors->getColoredString($prompt, $color);
        
        return trim(fgets(STDIN));
    }
    
    // Display menu with items and short descriptions
    public function menu($msg, $items, $list) {
        if (count($items) !== count($list)) {
            $this->error("UTILS: Menu parameters not the same size!");
            return;
        }
        
        echo "$msg\n";
        
        // Grab max item length
        $max = max(array_map("strlen", $items));
        
        foreach ($items as $key=>$item) {
            echo "   ".str_pad($item, $max, " ", STR_PAD_LEFT)."  ".$list[$key]."\n";
        }
    }
}
?>