package main
type double float64;
type float float64;
type size_t int;
var current_count = 0;
var INT, RUNE, FLOAT, BOOL, STRING int = 0,1,2,3,4;
type union_basic struct{
	u_type int;
	i_val int;
	r_val rune;
	f_val float;
	b_val bool;
	s_val string;
}
func print_basic(val union_basic){
	switch val.u_type{
		case 0: println(val.i_val);
		case 1: println(val.f_val);
		case 2: println(val.r_val)
		case 3: println(val.b_val)
		case 4: println(val.s_val);
		default:
			return;
		}
}
func stack_overflow(left, right []union_basic){
	print_basic(left[current_count]);
	print_basic(right[current_count]);
	var add union_basic;
	switch current_count % 5{
	case 0: add.u_type = 0; 
			add.i_val = (71332323 + current_count)%17; 
			break;
	case 1: add.u_type = 1;
			add.f_val = (float(72233.2) * float(2333) + float(current_count))/float('r');
			break;
	case 2:	add.u_type = 2;
			add.r_val = ('2' + '2' * rune(current_count)) % rune(243);
	case 3: 
			add.u_type = 3;
			var false = true;
			add.b_val = false; 
			break;
	case 4: 
			add.u_type = 4;
			add.s_val = add.s_val + "HUE HUE HUE \n";
	default:
			return;
	}
	left = append(left, add, add);
	right = append(right, add);
	current_count++;
	stack_overflow(left, right);
}
func main() {
	var left, right []union_basic;
	var test union_basic;
	left = append(left, test)
	right = append(right, test)
	stack_overflow(left, right);
}