
set canvas_size 700

canvas .board -width [expr $canvas_size + 10] -height [expr $canvas_size + 10]

proc draw_board {} {
    set canvas_size 700

    set game_date [game_proc]

    set sum_square_w  [lindex $game_date 3]
    set sum_square_h  [lindex $game_date 2]

    puts "sum_square_w : $sum_square_h"

    set square_size_w [expr {int($canvas_size / $sum_square_w)}]
    set square_size_h [expr {int($canvas_size / $sum_square_h)}]

    for {set n 0; set y 0} {$y < $sum_square_h} {incr y} {

        set xs 15
        set ys [expr $y * $square_size_h + 10]
        set xe $canvas_size
        set ye [expr $y * $square_size_h + 10]

        .board create line $xs [expr $ys - 5 + $square_size_h] $xe [expr $ye - 5 + $square_size_h]
        .board create line $xs [expr $ys + 5] $xe [expr $ye + 5]

        for {set x 0} {$x < $sum_square_w} {incr x} {
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

    set player_number [lindex $game_date 4]
    for {set i 0} {$i < $player_number} {incr i} {
        set center_x [expr ([lindex $game_date [expr $i * 3 + 5]] + 0.5) * $square_size_w]
        set center_y [expr ([lindex $game_date [expr $i * 3 + 6]] + 0.5) * $square_size_h]
        set xs [expr {int($center_x - (($square_size_w * 0.8) / 2))} + 10]
        set ys [expr {int($center_y - (($square_size_h * 0.8) / 2))} + 10]
        set xe [expr {int($center_x + (($square_size_w * 0.8) / 2))} + 10]
        set ye [expr {int($center_y + (($square_size_h * 0.8) / 2))} + 10]

        if {$i == 0} {
            set color "#FFFFFF"
        } else {
            set color "#000000"
        }
        .board create oval $xs $ys $xe $ye -fill $color
    }

    pack .board

    after 500 draw_board

}

draw_board
