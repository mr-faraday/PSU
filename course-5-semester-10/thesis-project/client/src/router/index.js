import store from '@/store'
import { createRouter, createWebHistory } from 'vue-router'
import dashboardItems from './dashboard'

/**
 * @type {import('vue-router').RouteRecordRaw[]}
 */
const routes = [
  {
    path: '/login',
    name: 'login',
    component: () => import('@views/LoginView.vue'),
  },
  {
    path: '/dashboard',
    name: 'dashboard',
    component: () => import('@views/DashboardView.vue'),
    async beforeEnter(to, from, next) {
      if (!store.getters['user/info']) {
        return next('/login')
      }

      next()
    },
    children: dashboardItems.map((item) => ({
      path: item.href,
      name: `dashboard-${item.name}`,
      component: () => import(`@views/dashboard/${item.component}`),
      meta: item.meta,
      beforeEnter(to, from, next) {
        const roleId = store.getters['user/info'].roleId
        if (item.roles && !item.roles.includes(roleId)) {
          return next('/dashboard')
        }

        next()
      },
    })),
  },

  { path: '/:pathMatch(.*)*', component: () => import('@views/IndexView.vue') },
]

const router = createRouter({
  history: createWebHistory(process.env.BASE_URL),
  routes,
  linkActiveClass: 'active',
})

export default router
