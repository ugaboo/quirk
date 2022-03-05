; ModuleID = 'module'
source_filename = "module"

@a = common global i64
@b = common global i64
@tmp = common global i64

define i32 @main() {
  store i64 1, i64* @a, align 4
  store i64 2, i64* @b, align 4
  %a = load i64, i64* @a, align 4
  store i64 %a, i64* @tmp, align 4
  %b = load i64, i64* @b, align 4
  store i64 %b, i64* @a, align 4
  %tmp = load i64, i64* @tmp, align 4
  store i64 %tmp, i64* @b, align 4
  ret i32 0
}
