; ModuleID = 'module'
source_filename = "module"

@a = common global i64 0
@b = common global i64 0
@c = common global i64 0

define i32 @main() {
  store i64 1, i64* @a, align 4
  store i64 2, i64* @b, align 4
  %a = load i64, i64* @a, align 4
  %b = load i64, i64* @b, align 4
  %add = add i64 %a, %b
  store i64 %add, i64* @c, align 4
  ret i32 0
}
