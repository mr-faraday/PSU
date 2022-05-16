const { defineConfig } = require('@vue/cli-service')
const path = require('path')

module.exports = defineConfig({
  transpileDependencies: true,
  // add import aliases
  configureWebpack: {
    resolve: {
      alias: {
        '@views': path.resolve(__dirname, 'src/views'),
        '@components': path.resolve(__dirname, 'src/components'),
        '@assets': path.resolve(__dirname, 'src/assets'),
        '@api': path.resolve(__dirname, 'src/api'),
        '@utils': path.resolve(__dirname, 'src/utils'),
        '@config': path.resolve(__dirname, 'src/config'),
        '@constants': path.resolve(__dirname, 'src/constants'),
        '@styles': path.resolve(__dirname, 'src/styles'),
      },
    },
  },
})
