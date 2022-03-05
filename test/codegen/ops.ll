; ModuleID = 'module'
source_filename = "module"

@i1 = common global i64 0
@f1 = common global double 0.000000e+00
@x = common global i64 0

define i32 @main() {
  store i64 42, i64* @i1, align 4
  store double 2.000000e+00, double* @f1, align 8
  %i1 = load i64, i64* @i1, align 4
  %f1 = load double, double* @f1, align 8
  %1 = fptosi double %f1 to i64
  %idiv = sdiv i64 %i1, %1
  store i64 %idiv, i64* @x, align 4
  ret i32 0
}
