from conan import ConanFile


class AmoraRecipe(ConanFile):
    settings = 'os', 'compiler', 'build_type', 'arch'
    generators = 'PremakeDeps'

    def requirements(self):
        self.requires('entt/3.12.2')
        self.requires('glm/cci.20230113')
