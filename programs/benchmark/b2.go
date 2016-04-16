package main

func main() {
	var n int = 100000;

	var b [100000]int;
	for i:= 0; i < n; i++{
	        if i % 2 == 0 { b[i] = 2; }
		if i % 3 == 0 { b[i] = 3; }
		if i % 2 == 0 { b[i] = 5; }
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

}