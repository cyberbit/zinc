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

/**
 * Colors class copied from http://www.if-not-true-then-false.com
 *
 * Reference from rlutil.h:
 *
 *   0 = black,
 *   1 = blue,
 *   2 = green,
 *   3 = cyan,
 *   4 = red,
 *   5 = magenta,
 *   6 = brown,
 *   7 = grey,
 *   8 = dark_grey,
 *   9 = light_blue,
 *  10 = light_green,
 *  11 = light_cyan,
 *  12 = light_red,
 *  13 = light_magenta,
 *  14 = yellow,
 *  15 = white
 */
class Colors {
    private $foreground_colors = array();
    private $background_colors = array();

    public function __construct() {
        // Set up shell colors
        $this->foreground_colors['black'] = '0;30';
        $this->foreground_colors['dark_gray'] = '1;30';
        $this->foreground_colors['blue'] = '0;34';
        $this->foreground_colors['light_blue'] = '1;34';
        $this->foreground_colors['green'] = '0;32';
        $this->foreground_colors['light_green'] = '1;32';
        $this->foreground_colors['cyan'] = '0;36';
        $this->foreground_colors['light_cyan'] = '1;36';
        $this->foreground_colors['red'] = '0;31';
        $this->foreground_colors['light_red'] = '1;31';
        $this->foreground_colors['purple'] = '0;35';
        $this->foreground_colors['light_purple'] = '1;35';
        $this->foreground_colors['brown'] = '0;33';
        $this->foreground_colors['yellow'] = '1;33';
        $this->foreground_colors['light_gray'] = '0;37';
        $this->foreground_colors['white'] = '1;37';

        $this->background_colors['black'] = '40';
        $this->background_colors['red'] = '41';
        $this->background_colors['green'] = '42';
        $this->background_colors['yellow'] = '43';
        $this->background_colors['blue'] = '44';
        $this->background_colors['magenta'] = '45';
        $this->background_colors['cyan'] = '46';
        $this->background_colors['light_gray'] = '47';
    }

    // Returns colored string
    public function getColoredString($string, $foreground_color = null, $background_color = null) {
        $colored_string = "";

        // Check if given foreground color found
        if (isset($this->foreground_colors[$foreground_color])) {
            $colored_string .= "\033[" . $this->foreground_colors[$foreground_color] . "m";
        }
        // Check if given background color found
        if (isset($this->background_colors[$background_color])) {
            $colored_string .= "\033[" . $this->background_colors[$background_color] . "m";
        }

        // Add string and end coloring
        $colored_string .=  $string . "\033[0m";

        return $colored_string;
    }

    // Returns all foreground color names
    public function getForegroundColors() {
        return array_keys($this->foreground_colors);
    }

    // Returns all background color names
    public function getBackgroundColors() {
        return array_keys($this->background_colors);
    }
}

/**
 * BasicEnum class copied from http://stackoverflow.com/a/254543/3402854
 */
abstract class BasicEnum {
    private static $constCacheArray = NULL;

    private static function getConstants() {
        if (self::$constCacheArray == NULL) {
            self::$constCacheArray = [];
        }
        $calledClass = get_called_class();
        if (!array_key_exists($calledClass, self::$constCacheArray)) {
            $reflect = new ReflectionClass($calledClass);
            self::$constCacheArray[$calledClass] = $reflect->getConstants();
        }
        return self::$constCacheArray[$calledClass];
    }

    public static function isValidName($name, $strict = false) {
        $constants = self::getConstants();

        if ($strict) {
            return array_key_exists($name, $constants);
        }

        $keys = array_map('strtolower', array_keys($constants));
        return in_array(strtolower($name), $keys);
    }

    public static function isValidValue($value, $strict = true) {
        $values = array_values(self::getConstants());
        return in_array($value, $values, $strict);
    }
}

?>