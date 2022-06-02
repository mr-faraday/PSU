import { createApp } from 'vue'
import App from './App.vue'
import router from './router'
import store from './store'

import Toast, { POSITION } from 'vue-toastification'
import 'vue-toastification/dist/index.css'

createApp(App)
  .use(store)
  .use(Toast, { timeout: 3000, position: POSITION.BOTTOM_RIGHT })
  .use(router)
  .mount('#app')
