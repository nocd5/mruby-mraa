MRuby::Gem::Specification.new('mruby-mraa') do |spec| 
  spec.license = 'MIT'
  spec.authors = 'nocd5'

  spec.linker.libraries << [ 'mraa' ]
end
