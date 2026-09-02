#!/usr/bin/env bash
set -euo pipefail

root_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
backup_dir="$(mktemp -d)"

restore_kicad_sources() {
  if [[ -d "$backup_dir" ]]; then
    (
      cd "$backup_dir"
      find . -type f -print0
    ) | while IFS= read -r -d '' rel_file; do
      mkdir -p "$(dirname "$root_dir/$rel_file")"
      cp -p "$backup_dir/$rel_file" "$root_dir/$rel_file"
    done
    rm -rf "$backup_dir"
  fi
}

add_svg_background() {
  local svg="$1"
  local color="$2"
  local tmp
  tmp="$(mktemp)"

  awk -v color="$color" '
    {
      print
      if (!done) {
        if ($0 ~ /^<svg([[:space:]]|$)/) {
          in_svg = 1
        }
        if (in_svg && $0 ~ />[[:space:]]*$/) {
          print "<rect x=\"0\" y=\"0\" width=\"100%\" height=\"100%\" fill=\"" color "\"/>"
          done = 1
        }
      }
    }
  ' "$svg" > "$tmp"

  mv "$tmp" "$svg"
  sed -i 's/[[:space:]]*$//' "$svg"
}

apply_pcb_editor_style() {
  local svg="$1"

  sed -i \
    -e 's/#C83434; fill-opacity:1\.0000/#C83434; fill-opacity:0.6500/g' \
    -e 's/#C83434; stroke-width:\([^;]*\); stroke-opacity:1;/#C83434; stroke-width:\1; stroke-opacity:0.6500;/g' \
    "$svg"
}

trap restore_kicad_sources EXIT

if ! command -v kicad-cli >/dev/null 2>&1; then
  echo "error: kicad-cli not found in PATH" >&2
  exit 1
fi

shopt -s nullglob

boards=()
for dir in "$root_dir"/*/; do
  pcb_files=("$dir"/*.kicad_pcb)
  if (( ${#pcb_files[@]} == 1 )); then
    boards+=("${pcb_files[0]}")
  elif (( ${#pcb_files[@]} > 1 )); then
    echo "warning: skipping $dir because it has multiple .kicad_pcb files" >&2
  fi
done

if (( ${#boards[@]} == 0 )); then
  echo "error: no board directories with .kicad_pcb files found under $root_dir" >&2
  exit 1
fi

while IFS= read -r -d '' source_file; do
  rel_file="${source_file#$root_dir/}"
  mkdir -p "$backup_dir/$(dirname "$rel_file")"
  cp -p "$source_file" "$backup_dir/$rel_file"
done < <(
  find "$root_dir" -mindepth 2 -maxdepth 2 -type f \
    \( -name '*.kicad_pcb' -o -name '*.kicad_sch' -o -name '*.kicad_pro' -o -name '*.kicad_prl' \) \
    -print0
)

for pcb in "${boards[@]}"; do
  board_dir="$(dirname "$pcb")"
  board_name="$(basename "$pcb" .kicad_pcb)"
  sch="$board_dir/$board_name.kicad_sch"
  out_dir="$board_dir/renders"

  echo "==> $board_name"
  mkdir -p "$out_dir"
  rm -f \
    "$out_dir/$board_name-pcb-front.svg" \
    "$out_dir/$board_name-pcb-back.svg"

  kicad-cli pcb export svg \
    --mode-single \
    --page-size-mode 2 \
    --exclude-drawing-sheet \
    --layers B.Cu,F.Cu,B.Silkscreen,F.Silkscreen,Edge.Cuts \
    --output "$out_dir/$board_name-pcb.svg" \
    "$pcb"
  add_svg_background "$out_dir/$board_name-pcb.svg" "#ffffff"
  apply_pcb_editor_style "$out_dir/$board_name-pcb.svg"

  if [[ -f "$sch" ]]; then
    kicad-cli sch export svg \
      --output "$out_dir" \
      "$sch"
    add_svg_background "$out_dir/$board_name.svg" "#ffffff"
  else
    echo "warning: no matching schematic found for $pcb" >&2
  fi
done
