
set canvas_size 700

canvas .board -width [expr $canvas_size + 10] -height [expr $canvas_size + 10]

set square_size_w [expr {int($canvas_size / 9)}]
set square_size_h [expr {int($canvas_size / 8)}]

for {set n 0; set y 0} {$y < 8} {incr y} {
    for {set x 0} {$x < 9} {incr x} {
        set xs [expr $x * $square_size_w + 10]
        set ys [expr $y * $square_size_h + 10]
        set xe [expr ($x + 1) * $square_size_w + 10]
        set ye [expr ($y + 1) * $square_size_h + 10]

        set tag_name [format "square_%d_%d" $x $y]

        set i [.board create rectangle $xs $ys $xe $ye -tags $tag_name]
    }
}

pack .board