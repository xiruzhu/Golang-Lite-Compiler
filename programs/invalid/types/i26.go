package main

type usedHaskell bool
type huehuehue usedHaskell
type fact huehuehue;
type float float64

type compiler struct{
	bad_language usedHaskell;
	fast_compile huehuehue
	worship_c fact
	compile_time float;
}

func new_compiler(bad_language, fast_compile, worship_c bool, compile_time float64) compiler {
	var ret compiler;
	ret.bad_language = usedHaskell(bad_language);
	ret.fast_compile = huehuehue(fast_compile);
	ret.worship_c = fact(worship_c);
	ret.compile_time = float(compile_time);
	println("Acknowledge Your Masters = ", ret.worship_c);
	return ret;
}

func main(){
	var best_compiler = (new_compiler(false, true, true, .005));
	var haskell_compiler = (new_compiler(true, false, false, 2000.0));
	if(best_compiler == haskell_compiler){
		println(4 % 4.5);
	}else{
		println("Best Compiler Time: ", best_compiler.compile_time)
	}
}