; ModuleID = 'module'
source_filename = "module"

define i32 @main() {
  ret i32 0
}

define void @foo() {
  ret void
}

define i64 @bar() {
  ret i64 0
}

define double @baz(i64 %a, double %b) {
  ret double 0.000000e+00
}
