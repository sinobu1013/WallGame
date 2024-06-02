
set canvas_size 700

canvas .board -width [expr $canvas_size + 10] -height [expr $canvas_size + 10]

set square_size_w [expr {int($canvas_size / 9)}]
set square_size_h [expr {int($canvas_size / 8)}]

for {set n 0; set y 0} {$y < 8} {incr y} {

    set xs 15
    set ys [expr $y * $square_size_h + 10]
    set xe $canvas_size
    set ye [expr $y * $square_size_h + 10]

    .board create line $xs [expr $ys - 5 + $square_size_h] $xe [expr $ye - 5 + $square_size_h]
    .board create line $xs [expr $ys + 5] $xe [expr $ye + 5]

    for {set x 0} {$x < 9} {incr x} {
        set xs [expr $x * $square_size_w + 10 + 5]
        set ys [expr $y * $square_size_h + 10 + 5]
        set xe [expr ($x + 1) * $square_size_w + 10 - 5]
        set ye [expr ($y + 1) * $square_size_h + 10 - 5]

        set tag_name [format "square_%d_%d" $x $y]

        set i [.board create rectangle $xs $ys $xe $ye -tags $tag_name -fill green]

        set xs [expr $x * $square_size_w + 10]
        set ys 15
        set xe [expr $x * $square_size_w + 10]
        set ye [expr $canvas_size]
        .board create line [expr $xs - 5 + $square_size_w] $ys [expr $xe - 5 + $square_size_w] $ye
        .board create line [expr $xs + 5] $ys [expr $xe + 5] $ye
    }
}

pack .board