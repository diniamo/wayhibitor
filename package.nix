{stdenv, commit, lib, wayland}:
stdenv.mkDerivation {
  pname = "wayhibitor";
  version = "0-unstable-${commit}";

  src = lib.cleanSource ./.;

  buildInputs = [wayland];
  makeFlags = ["PREFIX=$(out)"];

  meta = {
    description = "Manual wayland idle inhibitor written in C";
    homepage = "https://github.com/diniamo/wayhibitor";
    license = lib.licenses.eupl12;
    platforms = lib.platforms.unix;
    maintainers = [lib.maintainers.diniamo];
    mainProgram = "wayhibitor";
  };
}
