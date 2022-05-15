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
        '@router': path.resolve(__dirname, 'src/router'),
        '@store': path.resolve(__dirname, 'src/store'),
        '@api': path.resolve(__dirname, 'src/api'),
        '@utils': path.resolve(__dirname, 'src/utils'),
        '@mixins': path.resolve(__dirname, 'src/mixins'),
        '@plugins': path.resolve(__dirname, 'src/plugins'),
        '@filters': path.resolve(__dirname, 'src/filters'),
        '@directives': path.resolve(__dirname, 'src/directives'),
        '@i18n': path.resolve(__dirname, 'src/i18n'),
        '@config': path.resolve(__dirname, 'src/config'),
        '@constants': path.resolve(__dirname, 'src/constants'),
        '@services': path.resolve(__dirname, 'src/services'),
        '@mock': path.resolve(__dirname, 'src/mock'),
      },
    },
  },
})
