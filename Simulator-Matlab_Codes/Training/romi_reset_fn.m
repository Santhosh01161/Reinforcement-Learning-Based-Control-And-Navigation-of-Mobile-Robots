function in = romi_reset_fn(in)

x0 = 0;
y0 = 0;
theta0 = 0;

%r = rand(1) + 1.0;
r = 1.0;
deg = rand(1) * 2 * pi;

waypoint = round([r * cos(deg), r * sin(deg)], 2);

in = in.setVariable('theta0',theta0);
in = in.setVariable('x0',x0);
in = in.setVariable('y0',y0);
in = in.setVariable('waypoint', waypoint);