require 'rake'

phone = 'iPhsidus'

task :default => [:run]

desc "Builds and installs pebble app to watch, and then starts watching logs"
task :run do
  cmd = "pebble build && "
  cmd += "pebble install --phone #{phone}"
  sh cmd
  sleep 1
  cmd = "pebble logs --phone #{phone}"
  sh cmd
end