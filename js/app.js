$(function() {
    var ALPHABET = 'ABCDEFGHIJKLM/NOPQRSTUVWXYZ';
    
    var ALPHABET_MATRIX = [
        [
            ['A', 'B', 'C'],
            ['D', 'E', 'F'],
            ['G', 'H', 'I']
        ],
        [
            ['J', 'K', 'L'],
            ['M', '/', 'N'],
            ['O', 'P', 'Q']
        ],
        [
            ['R', 'S', 'T'],
            ['U', 'V', 'W'],
            ['X', 'Y', 'Z']
        ]
    ];
    
    console.log("alphabet: %o", ALPHABET);
    console.log("alphabet matrix: %o", ALPHABET_MATRIX);
    
    // Debug alphabet index
    /*$.each(ALPHABET.split(''), function(i, v) {
        console.log("index of %o: %o", v, JSON.stringify(reduceIndex(alphabetIndex(ALPHABET, v))));
    });*/
    
    // Debug reduction
    console.log("HEMPF reduces to %o", stringToReduction(ALPHABET, "HEMPF"));
});

function alphabetIndex(alphabet, value) {
    /**
     * Decoding cheat sheet (slice-row-column = z-y-x)
     *
     * Index 0-8:                               0-y-x
     * Index 9-17:                              1-y-x
     * Index 18-26:                             2-y-x
     *
     * Index 0-2, 9-11, 18-20:                  z-0-x
     * Index 3-5, 12-14, 21-23:                 z-1-x
     * Index 6-8, 15-17, 24-26:                 z-2-x
     *
     * Index 0, 3, 6, 9, 12, 15, 18, 21, 24:    z-y-0
     * Index 1, 4, 7, 10, 13, 16, 19, 22, 25:   z-y-1
     * Index 2, 5, 8, 11, 14, 17, 20, 23, 26:   z-y-2
     */
    
    if (alphabet.length != 27) {
        console.error("Incorrect alphabet length: %o", alphabet.length);
        return false;
    }
    
    var i = alphabet.indexOf(value);
    
    // Unknown character
    if (i == -1) {
        console.error("Unknown character: %o", value);
        return false;
    }
    
    var z = parseInt(i / 9);
    var y = parseInt(i / 3) % 3;
    var x = i % 3;
    
    return [z, y, x];
}

function reduceIndex(index) {
    return [index[0] + 1, index[1]*3 + index[2] + 1];
}

function stringToReduction(alphabet, string) {
    return string.split('').map(function(v) {
        return reduceIndex(alphabetIndex(alphabet, v));
    });
}