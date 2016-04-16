package main
var seed int = 172012
func rand(max int) int {
	seed = (69069 * seed + 1) % 260599465
	if max != 0 {
		if seed <= 0 {
			seed *= -1
		}
		return seed % max
	} else {
		return seed
	}
}

func main() {
	var n int = 1000;

	var b [1000]int;
	for i:= 0; i < n; i++{
	    b[i] = rand(100);
	}
	for{
		var flag = false;
		var i int;
		for i = 1; i < n; i ++ {
			if b[ i-1 ] > b [i] {
				var tmp int = b[i];
				b[i] = b[i-1];
				b[i-1] = tmp;
				flag  = true;
			}
		}
		n = n - 1;
		if !flag {
			break
		}
	}
	println(b);
}